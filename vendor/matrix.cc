// BSD 2-Clause License
//
// Copyright (c) 2016, frzifus
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "./matrix.h"
#include "./vector.h"

#include <stdexcept>  // std::invalid_argument

CMyMatrix::CMyMatrix(size_type height, size_type width) {
  width_ = width;
  height_ = height;
  value_.resize(width_);

  for (std::vector<CMyVektor>::iterator it = value_.begin(); it != value_.end();
       ++it) {
    (*it).ResetVector(height_);
  }
}

bool CMyMatrix::inversion() {
  if (height_ == 2 && width_ == 2) {
    double det = value_[0][0] * value_[1][1] - value_[1][0] * value_[0][1];
    if (det != 0) {
      CMyMatrix x = CMyMatrix(height_, width_);  // n height m width
      for (std::size_t i = 0; i < 2; i++) {
        for (std::size_t j = 0; j < 2; j++) {
          x[i][j] = value_[i][j];
        }
      }
      value_[0][0] = 1 / det * x[1][1];
      value_[1][0] = -(1 / det * x[1][0]);
      value_[0][1] = -(1 / det * x[0][1]);
      value_[1][1] = 1 / det * x[0][0];
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

std::ostream& operator<<(std::ostream& os, const CMyMatrix& m) {
  os << std::endl;
  for (std::size_t i{}; i < m.height_; i++) {
    os << "                ";
    if (i == 0) {
      os << "( ";
    }
    for (std::size_t j{}; j < m.width_; j++) {
      if (j > 0) {
        os << "; ";
      }
      os << m[j][i];
    }
    if (i < m.height_ - 1) {
      os << std::endl;
    }
  }
  os << " )";

  return os;
}

void CMyMatrix::set_height(size_type height) { height_ = height; }

CMyVektor operator*(CMyMatrix A, CMyVektor x) {
  if (A.width() != x.Dimensions()) {
    throw std::invalid_argument{"Vector height and matrix width do not match."};
  }

  CMyVektor vRes(A.height());
  for (std::size_t i{}; i < vRes.Dimensions(); ++i) {
    double sum = 0;
    for (std::size_t j{}; j < A.width(); ++j) {
      sum += A[j][i] * x[j];
    }
    vRes[i] = sum;
  }
  return vRes;
}

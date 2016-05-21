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

#include "./vector.h"

#include <algorithm>  // std::accumulate
#include <cmath>      // std::sqrt std::pow
#include <iostream>   // std::ostream
#include <numeric>

using size_type = CMyVektor::size_type;

CMyVektor::CMyVektor(size_type dimensions) {
  dimensions_ = dimensions;
  value_.resize(dimensions_);
}

void CMyVektor::ResetVector(size_type dimensions) {
  dimensions_ = dimensions;
  value_.clear();
  value_.resize(dimensions_);
}

double CMyVektor::length() const {
  return std::sqrt(std::accumulate(
      value_.begin(), value_.end(), 0.0,
      [](double sum, double value) { return sum + value * value; }));
}

CMyVektor operator+(CMyVektor a, const CMyVektor& b) {
  for (size_type i = 0; i < a.Dimensions(); ++i) {
    a[i] += b[i];
  }
  return a;
}

CMyVektor operator-(CMyVektor a, const CMyVektor& b) {
  for (size_type i = 0; i < a.Dimensions(); ++i) {
    a[i] -= b[i];
  }
  return a;
}

CMyVektor operator*(double lamda, CMyVektor a) {
  for (size_type i = 0; i < a.Dimensions(); ++i) {
    a[i] = a[i] * lamda;
  }
  return a;
}

CMyVektor operator*(CMyVektor a, const CMyVektor& b) {
  for (size_type i = 0; i < a.Dimensions(); ++i) {
    a[i] = a[i] * b[i];
  }
  return a;
}

std::ostream& operator<<(std::ostream& os, const CMyVektor& v) {
  os << "( ";
  for (size_type i = 0; i < v.Dimensions(); ++i) {
    os << v[i];
    if (i < v.Dimensions() - 1) {
      os << "; ";
    }  // trololololololol......
  }
  os << ")";
  return os;
}

void CMyVektor::inversion() {
  for (std::vector<double>::iterator it = value_.begin(); it != value_.end();
       ++it) {
    *it = *it - (*it * 2);
  }
}

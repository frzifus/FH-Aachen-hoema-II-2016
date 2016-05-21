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

#ifndef MY_MATRIX_H_
#define MY_MATRIX_H_

#include "./vector.h"

#include <cstddef>   // std::size_t
#include <iostream>  // std::ostream
#include <vector>    // std::vector

class CMyMatrix {
 public:
  using size_type = std::size_t;
  explicit CMyMatrix(size_type width = 1, size_type height = 1);
  bool inversion();

  size_type width() { return width_; }
  void set_height(size_type height);
  size_type height() { return height_; }

  CMyVektor& operator[](size_type i) { return value_.at(i); };
  CMyVektor operator[](size_type i) const { return value_.at(i); };

  friend std::ostream& operator<<(std::ostream& os, const CMyMatrix& v);
  friend CMyVektor operator*(CMyMatrix A, CMyVektor x);
  void print() {}

 private:
  size_type width_;
  size_type height_;
  std::vector<CMyVektor> value_;
};

#endif  // MY_MATRIX_H_

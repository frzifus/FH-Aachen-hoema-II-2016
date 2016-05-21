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

#ifndef MY_VEKTOR_H_
#define MY_VEKTOR_H_

#include <cstddef>   // std::size_t
#include <iostream>  // std::ostream
#include <vector>    // std::vector

class CMyVektor {
 public:
  using size_type = std::size_t;
  explicit CMyVektor(size_type dimension = 1);
  void ResetVector(size_type dimension);

  size_type Dimensions() const { return dimensions_; }
  double length() const;

  void inversion();

  double& operator[](size_type i) { return value_.at(i); };
  double operator[](size_type i) const { return value_.at(i); };

  friend std::ostream& operator<<(std::ostream& os, const CMyVektor& v);

  friend CMyVektor operator+(CMyVektor a, const CMyVektor& b);
  friend CMyVektor operator-(CMyVektor a, const CMyVektor& b);
  friend CMyVektor operator*(double lambda, CMyVektor a);
  friend CMyVektor operator*(CMyVektor a, const CMyVektor& b);

 private:
  size_type dimensions_;
  std::vector<double> value_;
};

#endif  // MY_VEKTOR_H_

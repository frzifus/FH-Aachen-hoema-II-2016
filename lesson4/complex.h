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

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <iostream>
#include <vector>

class Complex {
 private:
  double re, im;

 public:
  Complex() : re(0), im(0) {}
  Complex(const double& Re, const double& Im);
  Complex(const double& phi);

  double length() const;

  double Re() const { return re; }
  double Im() const { return im; }

  friend std::ostream& operator<<(std::ostream& stream, const Complex& c);

  void operator+=(const double& a);
  void operator+=(const Complex& a);
  void operator*=(const double& a);
  void operator*=(const Complex& a);

  friend bool operator==(const double& a, const Complex& b);
  friend bool operator==(const Complex& a, const double& b);
  friend bool operator==(const Complex& a, const Complex& b);
  friend bool operator!=(const double& a, const Complex& b);
  friend bool operator!=(const Complex& a, const double& b);
  friend bool operator!=(const Complex& a, const Complex& b);

  friend Complex operator+(const Complex& a, const Complex& b);
  friend Complex operator+(const double& a, const Complex& b);
  friend Complex operator*(const Complex& a, const Complex& b);
  friend Complex operator*(const double& a, const Complex& b);
};

#endif  // COMPLEX_H_

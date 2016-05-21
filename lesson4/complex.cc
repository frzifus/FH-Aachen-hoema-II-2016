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

#include "./complex.h"

#include <cmath>

Complex::Complex(const double& Re, const double& Im) : re(Re), im(Im) {}

Complex::Complex(const double& phi) : re(cos(phi)), im(sin(phi)) {}

double Complex::length() const { return sqrt(pow(re, 2) + pow(im, 2)); }

std::ostream& operator<<(std::ostream& stream, const Complex& c) {
  stream << c.re;
  if (c.im != 0) stream << (c.im > 0 ? " + " : " - ") << std::abs(c.im) << "i";
  return stream;
}

void Complex::operator+=(const double& a) { (*this) = (*this) + Complex(a, 0); }

void Complex::operator+=(const Complex& a) { (*this) = (*this) + a; }

void Complex::operator*=(const double& a) { (*this) = (*this) * Complex(a, 0); }

void Complex::operator*=(const Complex& a) { (*this) = (*this) * a; }

Complex operator+(const double& a, const Complex& b) {
  return Complex(a, 0) + b;
}

Complex operator+(const Complex& a, const Complex& b) {
  return Complex(a.re + b.re, a.im + b.im);
}

Complex operator*(const double& a, const Complex& b) {
  return Complex(a, 0) * b;
}

Complex operator*(const Complex& a, const Complex& b) {
  return Complex(a.re * b.re - a.im * b.im,   // Re
                 a.re * b.im + a.im * b.re);  // Im
}

bool operator==(const double& a, const Complex& b) {
  return Complex(a, 0) == b;
}

bool operator==(const Complex& a, const double& b) {
  return a == Complex(b, 0);
}

bool operator==(const Complex& a, const Complex& b) {
  return (a.re == b.re && a.im == b.im);
}

bool operator!=(const double& a, const Complex& b) {
  return Complex(a, 0) != b;
}

bool operator!=(const Complex& a, const double& b) {
  return a != Complex(b, 0);
}

bool operator!=(const Complex& a, const Complex& b) {
  return (a.re != b.re || a.im != b.im);
}

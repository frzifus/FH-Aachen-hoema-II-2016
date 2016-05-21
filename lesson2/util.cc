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

#include <cmath>       // std::sqrt
#include <cstddef>     // std::size_t
#include <functional>  // std::function
#include <iostream>    // std::cout std::endl std::ostream&
#include <string>      // std::string

namespace util {  // namespace util

CMyVektor test1(CMyVektor v) {
  CMyVektor res = CMyVektor(3);
  double x1 = v[0];
  double x2 = v[1];
  double x3 = v[2];
  double x4 = v[3];
  res[0] = x1 * x2 * std::exp(x3);
  res[1] = x2 * x3 * x4;
  res[2] = x4;
  return res;
}

CMyVektor test2(CMyVektor v) {
  CMyVektor res = CMyVektor(2);
  double x = v[0];
  double y = v[1];
  res[0] = x * x * x * y * y * y - 2 * y;
  res[1] = x - 2;
  return res;
}

CMyMatrix Jacobi(CMyVektor x, std::function<CMyVektor(CMyVektor)> func) {
  double h = 1E-4;
  CMyVektor temp;
  CMyMatrix y = CMyMatrix(x.Dimensions(), x.Dimensions());
  for (std::size_t i{0}; i < x.Dimensions(); ++i) {
    temp = x;
    temp[i] += h;

    for (std::size_t j{0}; j < func(x).Dimensions(); j++) {
      y[i][j] = (func(temp)[j] - func(x)[j]) / h;
    }
  }
  y.set_height(func(x).Dimensions());
  return y;
}

CMyVektor Newton(CMyVektor x, std::function<CMyVektor(CMyVektor)> func,
                 std::ostream &out) {
  std::size_t dim = x.Dimensions();
  int step = 0;
  double f_x_b = 1;
  CMyVektor f_x;
  std::string const W_SPACE = "         ";
  do {
    f_x = func(x);
    f_x_b = f_x.length();

    if (step > 51 || f_x_b < 1e-5) {
      break;
    }

    out << "Schritt " << step << ":" << std::endl;    //
    out << W_SPACE << "x = " << x << std::endl;       //
    out << W_SPACE << "f(x) = " << f_x << std::endl;  //
    CMyMatrix jacobi = CMyMatrix(dim, dim) = Jacobi(x, func);
    CMyVektor dx = CMyVektor(2);
    out << W_SPACE << "f'(x) = " << jacobi << std::endl;  //
    out << W_SPACE << "(f'(x))^(-1) =";                   //

    jacobi.inversion();
    std::cout << jacobi << std::endl;  //
    dx = jacobi * f_x;
    dx.inversion();
    out << W_SPACE << "dx = " << dx << std::endl;           //
    out << W_SPACE << "||f(x)|| = " << f_x_b << std::endl;  //
    x[0] = x[0] + dx[0];
    x[1] = x[1] + dx[1];

    step++;
  } while (step < 50 || step < 51);
  if (f_x_b < 1e-5) {
    out << "Ende wegen ||f(x)||<1e-5 bei " << std::endl;  //
  } else {
    out << "Ende nach 50 Schritten bei" << std::endl;  //
  }
  out << W_SPACE << "x = " << x << std::endl;             //
  out << W_SPACE << "f(x) = " << f_x << std::endl;        //
  out << W_SPACE << "||f(x)|| = " << f_x_b << std::endl;  //
  return x;
}

}  // namespace util

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
// sin(x + y²) + y³ - 6y² + 9y
double f(const CMyVektor& vektor) {
  auto x = vektor[0];
  auto y = vektor[1];
  return std::sin(x + y * y) + y * y * y - 6 * y * y + 9 * y;
}

// -(2*x² - 2x * y + y² + z² - 2x - 4z)
double g(const CMyVektor& vektor) {
  using std::pow;
  auto x = vektor[0];
  auto y = vektor[1];
  auto z = vektor[2];
  return -(2 * x * x - 2 * x * y + y * y + z * z - 2 * x - 4 * z);
}

CMyVektor Gradient(CMyVektor x, std::function<double(CMyVektor)> func) {
  CMyVektor result(x.Dimensions());
  double h = std::pow(10, -8);
  double f_x = func(x);
  for (std::size_t i = 0; i < x.Dimensions(); i++) {
    CMyVektor x_h = x;
    x_h[i] += h;
    result[i] = (func(x_h) - f_x) / h;
  }
  return result;
}

CMyVektor Gradientenverfahren(CMyVektor x,
                              std::function<double(CMyVektor)> func,
                              double lambda, std::ostream& out) {
  CMyVektor x_neu;
  x_neu = x;
  double const max_grad = std::pow(10, -5);
  int steps = 0;
  int const steps_max = 49;
  std::string const W_SPACE = "        ";
  for (; steps <= steps_max && (Gradient(x, func).length() >= max_grad);
       ++steps) {
    out << "Schritt " << steps << ":" << std::endl;        //
    out << W_SPACE << "x = " << x << std::endl;            //
    out << W_SPACE << "lambda = " << lambda << std::endl;  //
    out << W_SPACE << "f(x) = " << func(x) << std::endl;   //
    CMyVektor gradfx = Gradient(x, func);
    out << W_SPACE << "grad f(x) = (" << gradfx << ")" << std::endl;      //
    out << W_SPACE << "||grad f(x)|| = " << gradfx.length() << std::endl  //
        << std::endl;                                                     //

    x_neu = x + (lambda * Gradient(x, func));

    out << W_SPACE << "x_neu = " << x_neu << std::endl;          //
    out << W_SPACE << "f(x_neu) = " << func(x_neu) << std::endl  //
        << std::endl;                                            //

    if (func(x_neu) > func(x)) {
      // Teste mit doppelter Schrittweite
      CMyVektor x_test(x.Dimensions());
      x_test = x + ((2 * lambda) * Gradient(x, func));

      out << W_SPACE << "Teste mit doppelter Schrittweite (Lambda = "  //
          << 2 * lambda << "):" << std::endl;                          //
      out << W_SPACE << "x_test = " << x_test << std::endl;            //
      out << W_SPACE << "f(x_test) = " << func(x_test) << std::endl;   //

      if (func(x_test) > func(x_neu)) {
        // Verdopple Schrittweite"
        out << "        "
            << "Verdopple Schrittweite!"  //
            << std::endl
            << std::endl;  //
        lambda *= 2;
        x = x_test;
      } else {
        // Behalte alte Schrittweite bei
        out << W_SPACE << "behalte alte Scrhittweite!"  //
            << std::endl
            << std::endl;  //
        x = x_neu;
      }
    } else {
      do {
        // Halbiere Schrittweite
        lambda /= 2;
        out << W_SPACE << "Halbiere Schrittweite (lambda = "  //
            << lambda << "):" << std::endl;                   //
        x_neu = x + (lambda * Gradient(x, func));
        out << W_SPACE << "x_neu = " << x_neu << std::endl;  //
        out << W_SPACE << "f(x_neu) = " << func(x_neu)       //
            << std::endl
            << std::endl;  //

      } while (func(x_neu) <= func(x));
    }
    x = x_neu;
  }
  return x_neu;
}
}  // namespace util

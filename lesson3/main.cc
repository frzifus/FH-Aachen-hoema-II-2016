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

#include "./dgl_solver.h"
#include "./util.h"
#include "./vector.h"

#include <iostream>

int main() {
  C_DGLSolver T1{util::DGL_T1};
  C_DGLSolver T2{util::DGL_T2};

  CMyVektor vect1{2};
  vect1[0] = 0;
  vect1[1] = 1;

  CMyVektor vect2{3};
  vect2[0] = 1;
  vect2[1] = -1;
  vect2[2] = 2;

  char o;
  std::cout << "(1). EuerVerfahren" << std::endl;
  std::cout << "(2). HeunVerfahren" << std::endl;
  std::cout << "(3). Vergleiche   " << std::endl;
  std::cout << "Waehle: ";
  std::cin >> o;

  switch (o) {
    case '1': {
      T2.EulerVerfahren(1.0, 2.0, 0.001, vect2);
    } break;  // case 1
    case '2': {
      T2.HeunVerfahren(1.0, 2.0, 0.001, vect2);
    } break;  // case 2
    case '3': {
      for (int i{10}; i < 10000; i = i * 10) {
        std::cout << "Abweichung Euler bei " << i << " Schritten: ";
        std::cout << T2.EulerVerfahren(1.0, 2.0, 1.0 / i, vect2);
        std::cout << std::endl;
        std::cout << "Abweichung Heun bei " << i << " Schritten: ";
        std::cout << T2.HeunVerfahren(1.0, 2.0, 1.0 / i, vect2);
        std::cout << std::endl;
      }
    }
  }
  return 0;
}

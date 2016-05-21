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

#include "./util.h"
#include "./vector.h"

#include <iostream>
#include <string>

int main() {
  char o;
  std::cout << "(1). Call f(3, 2) lambda = 1"
               " -> sin(x + y²) + y³ - 6y² + 9y"
            << std::endl;
  std::cout << "(2). Call g(0,0,0) lambda = 0.1"
               " -> -(2*x² - 2x * y + y² + z² - 2x - 4z)"
            << std::endl;
  std::cout << "Waehle: ";
  std::cin >> o;

  switch (o) {
    case '1': {
      CMyVektor v1(2);
      v1[0] = 3;
      v1[1] = 2;
      std::cout << "v1 -> (3; 2) call f()" << std::endl;
      util::Gradientenverfahren(v1, util::f);
    } break;  // case 1
    case '2': {
      CMyVektor v2(3);
      v2[0] = 0;
      v2[1] = 0;
      v2[2] = 0;
      double lambda = 0.1;
      std::cout << "v2 -> (0; 0; 0) call g()" << std::endl;
      util::Gradientenverfahren(v2, util::g, lambda);
    } break;  // case 2
  }
  return 0;
}

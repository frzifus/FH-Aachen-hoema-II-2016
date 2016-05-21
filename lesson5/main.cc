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

#include "./lotto.h"
#include "./zufall.h"

#include <array>
#include <iostream>
#include <vector>

#include <ctime>

template <typename fwd>
void print(fwd first, fwd last) {
  for (std::vector<int>::iterator it = first; it != last; ++it) {
    std::cout << *it << '\n';
  }
  std::cout << std::flush;
}

double MonteCarloA() {
  Lotto A;
  double erg{0};
  std::vector<std::size_t> tip{5, 3, 15, 42, 33, 17};
  A.Tippen(tip.begin(), tip.end());
  for (std::size_t i{}; i < 1000000; ++i) {
    if (A.Spiel() == 3) {
      erg += 1;
    }
  }

  return erg / 10000;
}

double MonteCarloB() {
  Lotto B;
  double erg{0};
  for (int i = 0; i < 1000000; i++) {
    if (B.LottoAbweichung() == 3) {
      erg += 1;
    }
  }
  return erg / 10000;
}

int main() {
  /* Aufgabe 1

  Zufall rnd;
  std::vector<int> v;
  int n;
  std::cout << "Gib n ein hure!:";
  std::cin >> n;

  for (int i{}; i < 10; ++i) {
    if (i < 2) {
      std::cout << "Aufgabe a." << i + 1 << '\n';
      rnd.initialisiere(n);

    } else if (i > 1 && i < 6) {
      std::cout << "Aufgabe b." << i - 1 << '\n';
      rnd.initialisiere(i);
    } else {
      std::cout << "Aufgabe c." << i - 5 << '\n';
      rnd.initialisiere(std::time(nullptr));
    }
    v = rnd.test(3, 7, 10000);
    print(v.begin(), v.end());
    std::cout << std::endl;
    } */

  std::cout << "Wahrscheinlichkeit für 3 Richtige: " << MonteCarloA() << " %"
            << std::endl;
  std::cout << "Wahrscheinlichkeit für 3 gleiche bei 2 Ziehungen: "
            << MonteCarloB() << " %" << std::endl;
}

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

#include <algorithm>  // std::find

#include <ctime>

Lotto::Lotto(std::time_t n) {
  Zufall rnd_value;
  rnd_value_ = rnd_value;
  rnd_value_.initialisiere(n);
}

void Lotto::Tippen(std::vector<std::size_t>::iterator first,
                   std::vector<std::size_t>::iterator last) {
  for (auto it = first; it != last; ++it) {
    TippZettel_.push_back(*it);
  }
}

std::vector<std::size_t> Lotto::Ziehen_(std::size_t anzahl, std::size_t limit) {
  std::vector<std::size_t> ergebnis(anzahl);
  for (std::size_t i{}; i < anzahl; ++i) {
    std::size_t tmp;
    tmp = rnd_value_.wert(1, limit);
    if (ergebnis.end() != std::find(ergebnis.begin(), ergebnis.end(), tmp)) {
      --i;
      continue;
    }
    ergebnis.at(i) = tmp;
  }
  return ergebnis;
}

std::size_t Lotto::LottoAbweichung() {
  std::vector<std::size_t> tmp_1 = Ziehen_();
  std::vector<std::size_t> tmp_2 = Ziehen_();
  std::size_t ergebnis{};

  // TippZettel_ vergleiche mit Ziehung
  for (auto const &i : tmp_1) {
    for (auto const &j : tmp_2) {
      if (i == j) {
        ++ergebnis;
      }
    }
  }
  return ergebnis;
}

std::size_t Lotto::Spiel() {
  std::vector<std::size_t> tmp = Ziehen_();
  std::size_t ergebnis{};

  // TippZettel_ vergleiche mit Ziehung
  for (auto const &i : TippZettel_)
    for (auto const &j : tmp) {
      if (i == j) {
        ++ergebnis;
      }
    }
  return ergebnis;
}

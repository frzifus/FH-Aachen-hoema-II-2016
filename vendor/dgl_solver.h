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

#ifndef DGL_SOLVER_H_
#define DGL_SOLVER_H_

#include "./vector.h"

#include <functional>

struct StepData {
  double x;
  CMyVektor y;
  CMyVektor yDeriv;
  StepData(const double x, CMyVektor y, CMyVektor yDeriv)
      : x(x), y(y), yDeriv(yDeriv) {}
};

struct HeunData {
  StepData data;
  CMyVektor yTest;
  CMyVektor yDerivTest;
  CMyVektor yDerivMid;
  HeunData(StepData data, CMyVektor yTest, CMyVektor yDerivTest,
           CMyVektor yDerivMid)
      : data(data),
        yTest(yTest),
        yDerivTest(yDerivTest),
        yDerivMid(yDerivMid) {}
};

class C_DGLSolver {
 public:
  using size_type = int;

  C_DGLSolver(std::function<CMyVektor(CMyVektor, double)> f_DLG_System);
  C_DGLSolver(std::function<double(CMyVektor, double)> f_DLG_N_System);

  StepData EulerSchritt(const double h, StepData lastStep);
  HeunData HeunInfo(const double h, const double x, CMyVektor y);
  HeunData HeunSchritt(const double h, HeunData lastStep);

  CMyVektor EulerVerfahren(const double xStart, const double xEnd,
                           const double h, CMyVektor y_Start,
                           std::ostream &out = std::cout);
  CMyVektor HeunVerfahren(const double xStart, const double xEnd,
                          const double h, CMyVektor y_Start,
                          std::ostream &out = std::cout);

 private:
  bool isNthDGL = false;
  size_type i;
  std::function<CMyVektor(CMyVektor, double)> func_DGL;
  std::function<double(CMyVektor, double)> func_Nth_DGL;
  CMyVektor ableitung(CMyVektor y, double x);
};

#endif  // DGL_SOLVER_H_

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
#include "./vector.h"

#include <functional>

C_DGLSolver::C_DGLSolver(
    std::function<CMyVektor(CMyVektor, double)> F_DGL_System) {
  func_DGL = F_DGL_System;
}

C_DGLSolver::C_DGLSolver(
    std::function<double(CMyVektor, double)> F_DGL_N_System) {
  func_Nth_DGL = F_DGL_N_System;
  isNthDGL = true;
}

CMyVektor C_DGLSolver::ableitung(CMyVektor y, double x) {
  if (isNthDGL) {
    CMyVektor res{y.Dimensions()};
    for (std::size_t i{}; i < y.Dimensions() - 1; ++i) {
      res[i] = y[i + 1];
    }
    res[res.Dimensions() - 1] = func_Nth_DGL(y, x);
    return res;
  } else {
    return func_DGL(y, x);
  }
}

StepData C_DGLSolver::EulerSchritt(const double h, StepData lastStep) {
  lastStep.x += h;
  lastStep.y = h * lastStep.yDeriv + lastStep.y;
  lastStep.yDeriv = ableitung(lastStep.y, lastStep.x);
  return lastStep;
}

CMyVektor C_DGLSolver::EulerVerfahren(const double xStart, const double xEnd,
                                      const double h, CMyVektor y_Start,
                                      std::ostream &out) {
  int steps{};

  StepData data{xStart, y_Start, ableitung(y_Start, xStart)};

  out << "h = " << h << "\n\n";
  while (data.x < xEnd) {
    out << "Schritt " << steps << ":\n";
    out << "\tx = " << data.x << "\n";
    out << "\ty = " << data.y << "\n";
    out << "\ty' = " << data.yDeriv << "\n";

    if (isNthDGL) {
      out << std::endl;
      out << "\tAbweichung bei Scrhitt: " << steps + 1 << " "
          << data.y[0] - 0.5;
      out << std::endl;
    }

    data = EulerSchritt(h, data);
    ++steps;
  }

  out << "Ende bei\n";
  out << "\tx = " << data.x;
  out << "\ty = " << data.y;

  if (isNthDGL) {
    out << std::endl;
    out << "\tAbweichung bei Scrhitt: " << steps << " " << data.y[0] - 0.5;
    out << std::endl;
  }
  return data.y;
}

HeunData C_DGLSolver::HeunInfo(const double h, const double x, CMyVektor y) {
  double n{x};
  CMyVektor yDeriv = ableitung(y, n);
  // CMyVektor yDerivTest = ableitung(h * yDeriv + y, n);
  StepData euler{n, y, yDeriv};
  CMyVektor yDerivTest = EulerSchritt(h, euler).yDeriv;
  CMyVektor yDerivMid = 0.5 * (yDerivTest - yDeriv) + yDeriv;
  return HeunData{StepData{n, y, yDeriv}, y, yDerivTest, yDerivMid};
}

HeunData C_DGLSolver::HeunSchritt(const double h, HeunData lastStep) {
  lastStep.data.x += h;
  lastStep.data.y = lastStep.data.y + h * lastStep.yDerivMid;
  return HeunInfo(h, lastStep.data.x, lastStep.data.y);
}

CMyVektor C_DGLSolver::HeunVerfahren(const double xStart, const double xEnd,
                                     const double h, CMyVektor y_Start,
                                     std::ostream &out) {
  HeunData heun = HeunInfo(h, xStart, y_Start);
  int steps{};

  out << "h = " << h << "\n\n";

  while (heun.data.x < xEnd) {
    out << "Schritt " << steps << ":\n";
    out << "\tx = " << heun.data.x << "\n";
    out << "\ty = " << heun.data.y << "\n";
    out << "\ty'_orig = " << heun.data.yDeriv << "\n\n";
    out << "\ty_Test = " << heun.yTest << "\n";
    out << "\ty'_Test = " << heun.yDerivTest << "\n\n";
    out << "\ty'_Mittel = " << heun.yDerivMid << "\n\n";
    heun = HeunSchritt(h, heun);
    if (isNthDGL) {
      out << std::endl;
      out << "\tAbweichung bei Scrhitt: " << steps + 1 << " "
          << heun.data.y[0] - 0.5;
      out << std::endl;
    }

    ++steps;
  }

  out << "Ende bei\n";
  out << "\tx = " << heun.data.x;
  out << "\ty = " << heun.data.y;

  if (isNthDGL) {
    out << std::endl;
    out << "\tAbweichung bei Scrhitt: " << steps << " " << heun.data.y[0] - 0.5;
    out << std::endl;
  }
  return heun.data.y;
}

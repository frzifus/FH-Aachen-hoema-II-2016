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

#include <sys/stat.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "./compression.h"

#define PI 3.1415926536

std::vector<Complex> Compression::transform(const std::vector<Complex> &vec,
                                            std::size_t N, bool back) {
  std::vector<Complex> n_vec;
  const double AS = back ? 1 : -1;
  for (std::size_t n = 0; n < N; n++) {
    Complex res;
    for (std::size_t k = 0; k < N; k++) {
      res += vec.at(k) * Complex((AS * 2 * PI * static_cast<double>(k) *
                                  static_cast<double>(n)) /
                                 static_cast<double>(N));
    }
    res *= (1 / sqrt(static_cast<double>(N)));
    n_vec.push_back(res);
  }
  return n_vec;
}

void Compression::compressFile(const std::string &src,
                               const std::string &dest) {
  std::vector<Complex> vec = Compression::readFile(src);
  std::vector<Complex> n_vec = Compression::transform(vec, vec.size());
  Compression::writeFile(dest, n_vec, 0.1);
}

void Compression::decompressFile(const std::string &src,
                                 const std::string &dest) {
  std::vector<Complex> n_vec = Compression::readFile(src);
  std::vector<Complex> o_vec =
      Compression::transform(n_vec, n_vec.size(), DECOMPRESS);
  Compression::writeFile(dest, o_vec);
}

std::vector<Complex> Compression::readFile(const std::string &file) {
  std::size_t N, idx;
  double re, im;
  std::vector<Complex> value;
  std::ifstream fp;
  fp.open(file);
  if(!fp) {
    std::cout << "File not found." << std::endl;
    exit(1);
  }
  fp >> N;
  value.resize(N);

  while (!fp.eof()) {
    fp >> idx >> re >> im;
    value[idx] = Complex(re, im);
  }

  fp.close();

  return value;
}

void Compression::writeFile(const std::string &file,
                            const std::vector<Complex> &values,
                            const double &epsilon) {
  std::ofstream fp;
  fp.open(file);
  fp << values.size() << std::endl;
  for (std::size_t i{}; i < values.size(); ++i) {
    if (values[i].length() > epsilon)
      fp << i << "\t" << values[i].Re() << "\t" << values[i].Im() << std::endl;
  }
  fp.close();
}

long GetFileSize(std::string filename) {
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return rc == 0 ? stat_buf.st_size : -1;
}

double Compression::testCompression(const std::string &src, const double &start,
                                    const double &delta, const double &steps,
                                    const double &tolerance) {
  const std::string tmp = src + ".tmp";

  std::cout << std::fixed;

  double best_epsilon = start;

  const long src_length = GetFileSize(src);
  std::vector<Complex> origData = Compression::readFile(src);

  for (double epsilon = start; epsilon < (start + delta * steps);
       epsilon += delta) {
    std::vector<Complex> comprData =
        Compression::transform(origData, origData.size());
    Compression::writeFile(tmp, comprData, epsilon);
    comprData = Compression::readFile(tmp);
    const long dest_lenght = GetFileSize(tmp);
    std::vector<Complex> decomprData =
        Compression::transform(comprData, comprData.size(), DECOMPRESS);
    Compression::writeFile(tmp, decomprData);
    decomprData = Compression::readFile(tmp);

    double max_diff = 0;
    for (unsigned int i = 0; i < origData.size(); i++) {
      double diff = origData[i].Re() - decomprData[i].Re();
      // std::cout << diff << std::endl;
      // abs()
      if (diff < 0) {
        diff -= 2 * diff;  // * -1 trololol....
      }
      if (diff > max_diff) max_diff = diff;
    }

    double compression = 100 - static_cast<double>(dest_lenght) /
                                   static_cast<double>(src_length) * 100;

    std::cout << "Max deviation for ε = " << std::setprecision(2) << epsilon
              << ": " << std::setprecision(5) << max_diff
              << "\tCompression Rate: " << std::setprecision(2) << compression
              << "%" << (max_diff < tolerance ? "\t OK" : "\tFAIL")
              << std::endl;

    if (max_diff < tolerance) best_epsilon = epsilon;
  }

  remove(tmp.c_str());

  return best_epsilon;
}

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

#ifndef COMPRESSION_H_
#define COMPRESSION_H_

#include <iostream>
#include <vector>
#include "./complex.h"

#define COMPRESS false
#define DECOMPRESS true

class Compression {
 public:
  static std::vector<Complex> transform(const std::vector<Complex>& c,
                                        std::size_t N, bool back = COMPRESS);
  static void compressFile(const std::string& src, const std::string& dest);
  static void decompressFile(const std::string& src, const std::string& dest);
  static std::vector<Complex> readFile(const std::string& file);
  static void writeFile(const std::string& file,
                        const std::vector<Complex>& values,
                        const double& epsilon = -1);

  static double testCompression(const std::string& src, const double& start,
                                const double& delta, const double& steps,
                                const double& tolerance);
};

#endif  // COMPRESSION_H_

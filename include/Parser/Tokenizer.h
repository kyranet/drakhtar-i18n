// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <istream>

class Tokenizer {
  std::istream& stream_;

 protected:
  [[nodiscard]] inline char next() noexcept {
    if (finished()) return '\0';

    char out;
    stream_ >> out;
    return out;
  }

  [[nodiscard]] inline bool finished() noexcept { return stream_.eof(); }

 public:
  Tokenizer(std::istream& stream) : stream_(stream) {}
  Tokenizer(Tokenizer& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(Tokenizer&& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(const Tokenizer& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(const Tokenizer&& tokenizer) : stream_(tokenizer.stream_) {}
};

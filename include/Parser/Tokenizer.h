// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <cassert>
#include <istream>

class Tokenizer {
  std::istream& stream_;

 public:
  Tokenizer(std::istream& stream) : stream_(stream) {}
  Tokenizer(Tokenizer& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(Tokenizer&& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(const Tokenizer& tokenizer) : stream_(tokenizer.stream_) {}
  Tokenizer(const Tokenizer&& tokenizer) : stream_(tokenizer.stream_) {}

  [[nodiscard]] inline char next() noexcept {
    assert(!finished());

    char out;
    stream_.get(out);
    return out;
  }

  inline void undo() noexcept { stream_.unget(); }

  [[nodiscard]] inline bool finished() const noexcept { return stream_.eof(); }
};

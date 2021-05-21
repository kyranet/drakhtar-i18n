// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Parser/Tokenizer.h"

template <typename T>
class IParser {
  Tokenizer tokenizer_;

 protected:
  [[nodiscard]] inline Tokenizer& tokenizer() noexcept { return tokenizer_; }

  [[noreturn]] inline void unexpectedCharacter(char c,
                                               const std::string& type) {
    const auto uc = *reinterpret_cast<uint8_t*>(&c);
    throw std::runtime_error("Unexpected character '" + std::to_string(uc) +
                             "', " + type + " was expected.");
  }

  [[noreturn]] inline void unexpectedEndOfInput() {
    throw std::runtime_error("Unexpected end of input.");
  }

 public:
  IParser(std::istream& stream) : tokenizer_(stream) {}
  IParser(Tokenizer& t) : tokenizer_(t) {}

  virtual T run() = 0;
};

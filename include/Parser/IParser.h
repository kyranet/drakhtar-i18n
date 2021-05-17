// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Parser/Tokenizer.h"

template <typename T>
class IParser {
  Tokenizer tokenizer_;

 protected:
  [[nodiscard]] inline const Tokenizer& tokenizer() const noexcept {
    return tokenizer_;
  }

 public:
  IParser(std::istream& stream) : tokenizer_(stream) {}

  virtual T run() = 0;
};

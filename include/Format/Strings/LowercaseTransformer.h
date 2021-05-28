// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <algorithm>
#include <string>

#include "ITransformer.h"

class LowercaseTransformer : public ITransformer {
 public:
  std::string format(std::string s) override {
    std::for_each(s.begin(), s.end(), [](char& c) { c = ::tolower(c); });
    return s;
  }
};

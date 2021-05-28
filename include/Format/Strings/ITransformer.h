// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

class ITransformer {
 public:
  ITransformer() = default;
  virtual std::string format(std::string s) = 0;
};

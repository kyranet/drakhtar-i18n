// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

class INumber;

class Locale {
  std::string locale_{};
  INumber* numbers_{};

 public:
  [[nodiscard]] const std::string& locale() const noexcept { return locale_; }
  std::string& locale() noexcept { return locale_; }

  [[nodiscard]] const INumber* numbers() const noexcept { return numbers_; }
  INumber* numbers() noexcept { return numbers_; }
};

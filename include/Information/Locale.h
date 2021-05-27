// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "Parser/Strings/StringContent.h"

class INumber;

class Locale {
  std::string name_{};
  std::string locale_{};
  std::map<std::string, StringContent> keys_{};
  INumber* numbers_{};

  void load(const std::filesystem::path& path, const std::string& prefix);

 public:
  void init(const std::string& locale);
  void load();

  [[nodiscard]] const std::string& name() const noexcept { return name_; }

  [[nodiscard]] const std::string& locale() const noexcept { return locale_; }

  [[nodiscard]] const INumber* numbers() const noexcept { return numbers_; }
  INumber* numbers() noexcept { return numbers_; }
};

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
  /**
   * Initializes the locale's metadata from the `.meta.txt` file located in the
   * locale's dedicated directory.
   */
  void init(const std::string& locale);

  /**
   * Recursively loads all keys for the locale.
   */
  void load();

  /**
   * Gets the full locale's name.
   */
  [[nodiscard]] const std::string& name() const noexcept { return name_; }

  /**
   * Gets the ISO 631 code.
   */
  [[nodiscard]] const std::string& locale() const noexcept { return locale_; }

  /**
   * Gets the StringContent given a key.
   */
  [[nodiscard]] const StringContent& get(
      const std::string& key) const noexcept {
    return keys_.at(key);
  }

  /**
   * Gets the amount of loaded keys.
   */
  [[nodiscard]] size_t size() const noexcept { return keys_.size(); }

  [[nodiscard]] const INumber* numbers() const noexcept { return numbers_; }
  INumber* numbers() noexcept { return numbers_; }
};

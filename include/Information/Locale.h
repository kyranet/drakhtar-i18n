// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "Parser/Strings/StringContent.h"

class INumber;
class LocaleManager;
struct LocaleComponents;

class Locale {
  std::string name_{};
  std::string locale_{};
  std::map<std::string, StringContent> keys_{};
  LocaleManager& manager_;
  INumber* numbers_{};
  // TODO: IBool

  [[nodiscard]] std::string display(bool arg);
  [[nodiscard]] std::string display(int8_t arg);
  [[nodiscard]] std::string display(int16_t arg);
  [[nodiscard]] std::string display(int32_t arg);
  [[nodiscard]] std::string display(int64_t arg);
  [[nodiscard]] std::string display(uint8_t arg);
  [[nodiscard]] std::string display(uint16_t arg);
  [[nodiscard]] std::string display(uint32_t arg);
  [[nodiscard]] std::string display(uint64_t arg);
  [[nodiscard]] std::string display(float arg);
  [[nodiscard]] std::string display(double arg);

  void load(const std::filesystem::path& path, const std::string& prefix);
  void loadMetadata(const std::filesystem::path& path);
  bool loadFallback(const std::string& name);
  void loadFallbacks();

 public:
  Locale(LocaleManager& manager) : manager_(manager) {}

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

  std::string format(const std::string& arg...);
};

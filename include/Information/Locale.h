// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "Parser/Strings/StringContent.h"

class LocaleManager;
class NumberMetadata;
struct LocaleComponents;

class Locale {
  std::string name_{};
  std::string locale_{};
  uint32_t displayDigits_{6};
  std::map<std::string, StringContent> keys_{};
  std::map<std::string, std::string> assets_{};
  LocaleManager& manager_;
  NumberMetadata* numeric_;
  // TODO: IBool

  [[nodiscard]] const std::string& display(const std::string& arg) const;
  [[nodiscard]] std::string display(const char* arg) const;
  [[nodiscard]] std::string display(bool arg) const;
  [[nodiscard]] std::string display(int8_t arg) const;
  [[nodiscard]] std::string display(int16_t arg) const;
  [[nodiscard]] std::string display(int32_t arg) const;
  [[nodiscard]] std::string display(int64_t arg) const;
  [[nodiscard]] std::string display(uint8_t arg) const;
  [[nodiscard]] std::string display(uint16_t arg) const;
  [[nodiscard]] std::string display(uint32_t arg) const;
  [[nodiscard]] std::string display(uint64_t arg) const;
  [[nodiscard]] std::string display(float arg) const;
  [[nodiscard]] std::string display(double arg) const;
  [[nodiscard]] std::string displayMaybeExponent(double arg) const;
  [[nodiscard]] std::string displayExponent(double arg, int32_t exponent) const;
  [[nodiscard]] std::string displayNormal(double arg) const;

  void load(const std::filesystem::path& path, const std::string& prefix);
  void loadMetadata(const std::filesystem::path& path);
  bool loadFallback(const std::string& name);
  void loadFallbacks();

 public:
  Locale(LocaleManager& manager) : manager_(manager) {}

  /**
   * Initializes the locale's metadata from the `.meta.txt` file located in
   * the locale's dedicated directory.
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
   * Gets the maximum amount of digits allowed in both the integral and decimal
   * parts.
   */
  uint32_t displayDigits() const noexcept { return displayDigits_; }

  /**
   * Sets the maximum amount of digits allowed in both the integral and decimal
   * parts.
   */
  uint32_t& displayDigits() noexcept { return displayDigits_; }

  /**
   * Gets the StringContent given a key.
   */
  [[nodiscard]] const StringContent& get(
      const std::string& key) const noexcept {
    return keys_.at(key);
  }

  /**
   * Gets the asset route given a key.
   */
  [[nodiscard]] const std::string& getAsset(
      const std::string& key) const noexcept {
    return assets_.at(key);
  }

  /**
   * Gets the amount of loaded keys.
   */
  [[nodiscard]] size_t size() const noexcept { return keys_.size(); }

  /**
   * Gets the amount of loaded assets.
   */
  [[nodiscard]] size_t assetsSize() const noexcept { return assets_.size(); }

  [[nodiscard]] const NumberMetadata* numbers() const noexcept {
    return numeric_;
  }
  NumberMetadata* numbers() noexcept { return numeric_; }

  inline void nextArgument(std::vector<std::string>&) const noexcept {}

  template <typename T>
  inline void nextArgument(std::vector<std::string>& formatted,
                           T value) const noexcept {
    formatted.push_back(display(value));
  }

  template <typename T, typename... Args>
  inline void nextArgument(std::vector<std::string>& formatted, T value,
                           Args... args) const noexcept {
    formatted.push_back(display(value));
    nextArgument(formatted, args...);
  }

  template <typename... Args>
  std::string format(const std::string& key, Args... args) const {
    const auto& content = keys_.at(key);

    std::vector<std::string> formatted{};
    nextArgument(formatted, args...);

    return content.run(formatted);
  }
};

// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Information/Locale.h"

class LocaleManager final {
  bool initialized_{false};
  std::map<std::string, std::string> names_{};
  std::map<std::string, Locale> loaded_{};

  int32_t internalLoad(bool metadataOnly);
  bool internalLoad(const std::string& locale, bool metadataOnly);

 public:
  /**
   * Initializes the LocaleManager, loading all basic metadata.
   */
  void init();

  /**
   * Loads all locales.
   * @returns The amount of languages read.
   */
  int32_t load();

  /**
   * Loads a specific locale.
   * @returns Whether or not the load was successful.
   */
  bool load(const std::string& locale);

  [[nodiscard]] bool initialized() const noexcept { return initialized_; }

  [[nodiscard]] const std::map<std::string, std::string>& list() {
    return names_;
  }

  [[nodiscard]] bool has(const std::string& locale) const noexcept {
    return names_.find(locale) != names_.cend();
  }

  [[nodiscard]] bool loaded(const std::string& locale) const noexcept {
    return loaded_.find(locale) != loaded_.cend();
  }

  [[nodiscard]] const Locale& get(const std::string& locale) const noexcept {
    return loaded_.at(locale);
  }
};

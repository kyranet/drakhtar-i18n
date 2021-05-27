// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Information/Locale.h"

namespace Util {
struct Locale;
}

class LocaleManager final {
  bool initialized_{false};
  std::map<std::string, std::string> names_{};
  std::map<std::string, Locale> loaded_{};

  void init();

  int32_t load(bool metadataOnly);
  bool load(const std::string& locale, bool metadataOnly);

 public:
  int32_t load();
  bool load(const std::string& locale);

  [[nodiscard]] const std::map<std::string, std::string>& list() {
    return names_;
  }

  [[nodiscard]] const Locale& get(const std::string& locale) const noexcept {
    return loaded_.at(locale);
  }

  [[nodiscard]] static Util::Locale getPreferred() noexcept;
};

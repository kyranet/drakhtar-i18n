// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <cstdint>
#include <string>

struct LocaleComponents {
  enum class Type : uint8_t {
    None = 0b00,
    Country = 0b01,
    Script = 0b10,
    All = 0b11
  };

  std::string language;
  std::string script;
  std::string country;

  LocaleComponents(const std::string& locale) noexcept;
  LocaleComponents(const LocaleComponents& components) noexcept
      : language(components.language),
        script(components.script),
        country(components.country) {}
  LocaleComponents(LocaleComponents& components) noexcept
      : language(components.language),
        script(components.script),
        country(components.country) {}
  LocaleComponents(LocaleComponents&& components) noexcept
      : language(components.language),
        script(components.script),
        country(components.country) {}

  [[nodiscard]] Type type() const noexcept;
  [[nodiscard]] std::string string() const noexcept;
  [[nodiscard]] bool fallback(LocaleComponents& components) const noexcept;
  [[nodiscard]] bool fallback() noexcept { return fallback(*this); }
};

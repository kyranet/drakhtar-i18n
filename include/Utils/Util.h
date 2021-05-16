// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

namespace Util {
struct Locale {
  /**
   * The full name of the locale.
   * @example en_US.UTF-8
   */
  std::string name;

  /**
   * The ISO-639 language code.
   * @example en
   */
  std::string language;

  /**
   * The ISO-3199 country code.
   * @example US
   */
  std::string country;
};

/**
 * Check whether or not a character is an ASCII letter.
 */
[[nodiscard]] inline bool isLetter(char c) noexcept {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * Check whether or not a character is not an ASCII letter.
 */
[[nodiscard]] inline bool isNotLetter(char c) noexcept { return !isLetter(c); }

/**
 * Gets the user's preferred locale.
 */
Locale parseLocale(const std::string& locale) noexcept;

/**
 * Gets the user's preferred locale.
 */
Locale getLocale() noexcept;
};  // namespace Util

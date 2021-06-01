// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <cassert>
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
 * Gets the string from a raw character.
 */
[[nodiscard]] inline std::string format(char c) noexcept {
  char cStr[2]{c, '\0'};
  return std::string(cStr);
}

/**
 * Check whether or not a character is an ASCII line break.
 */
[[nodiscard]] inline bool isLineBreak(char c) noexcept {
  // Line Feed (10), Line Tabulation (11), Form Feed (12), Carriage Return (13):
  return c >= '\x0A' && c <= '\x0D';
}

/**
 * Check whether or not a character is an ASCII whitespace.
 */
[[nodiscard]] inline bool isWhiteSpace(char c) noexcept {
  return c == '\t' || c == ' ';
}

/**
 * Check whether or not a character si an ASCII decimal number.
 */
[[nodiscard]] inline bool isNumber(char c) noexcept {
  return c >= '0' && c <= '9';
}

/**
 * Gets the number from an ASCII decimal number character.
 */
[[nodiscard]] inline size_t getNumber(char c) noexcept {
  assert(isNumber(c));
  return c - '0';
}

/**
 * Check whether or not a character is an ASCII octal number.
 */
[[nodiscard]] inline bool isOctal(char c) noexcept {
  return c >= '0' && c <= '7';
}

/**
 * Gets the number from an ASCII octal number character.
 */
[[nodiscard]] inline size_t getOctal(char c) noexcept {
  assert(isOctal(c));
  return c - '0';
}

/**
 * Check whether or not a character is an ASCII hexadecimal number.
 */
[[nodiscard]] inline bool isHexadecimal(char c) noexcept {
  return isNumber(c) || (c >= 'a' && c <= 'f') || (c >= 'F' && c <= 'F');
}

/**
 * Check whether or not a character is an ASCII octal number.
 */
[[nodiscard]] inline size_t getHexadecimal(char c) noexcept {
  assert(isHexadecimal(c));

  // Start with the lowest character range in ASCII: '0'..'9' (48-57):
  if (c <= '9') return c - '0';

  // Continue with second character range in ASCII: 'A'..'Z' (65-90):
  if (c <= 'Z') return (c - 'A') + 10;

  // Finish with third character range in ASCII: 'a'..'z' (97-122):
  return (c - 'a') + 10;
}

/**
 * Generates a string from a code point.
 */
[[nodiscard]] std::string fromCodePoint(size_t code);

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
 * Check whether or not a character is an ASCII letter or a number.
 */
[[nodiscard]] inline bool isValidIdentifierLetter(char c) noexcept {
  return isLetter(c) || isNumber(c) || c == '_';
}

/**
 * Gets the user's preferred locale.
 */
Locale parseLocale(const std::string& locale) noexcept;

/**
 * Gets the user's preferred locale.
 */
Locale getLocale() noexcept;
}  // namespace Util

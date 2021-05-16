// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Utils/Util.h"

#include <algorithm>
#include <iostream>
#include <locale>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

namespace Util {
/**
 * Check whether or not a character is a dot.
 */
[[nodiscard]] inline bool isDot(char c) noexcept { return c == '.'; }

/**
 * Check whether or not a character is a semicolon.
 */
[[nodiscard]] inline bool isSemiColon(char c) noexcept { return c == ';'; }

/**
 * Gets the user's preferred locale.
 */
Locale parseLocale(const std::string& locale) noexcept {
  const auto length = locale.length();

  if (length < 2) {
    return {locale, "en", "US"};
  }

  // 2-letter languages (ISO 639-1: en, es, ...) or
  // 3-letter languages (ISO 639-2: eng, spa, ...):
  if (length <= 3) {
    return {locale, locale, ""};
  }

  const auto end = locale.cend();
  const auto languageIt = find_if(locale.cbegin(), end, isNotLetter);

  // Could not find a non-letter character, which suggests language-only locale.
  if (languageIt == end) {
    return {locale, locale, ""};
  }

  const auto language = locale.substr(0, languageIt - locale.cbegin());

  auto itOffset = language.length() + 1;
  const auto countryIt = find_if(locale.cbegin() + itOffset, end, isDot);

  if (countryIt == end) {
    const auto country = locale.substr(itOffset);
    return {locale, language, country};
  }

  const auto countryLength = countryIt - (locale.cbegin() + itOffset);
  const auto country = locale.substr(itOffset, countryLength);
  return {locale, language, country};
}

Locale getLocale() noexcept {
#if defined(_WIN32) || defined(_WIN64)
  wchar_t v[LOCALE_NAME_MAX_LENGTH]{0};
  auto len = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, v,
                             sizeof(v) / sizeof(wchar_t));

  if (len == 0) {
    return {"", "en", "US"};
  }

  const auto wide = std::wstring(v, len - 1);

  std::string locale(wide.size(), 0);
  std::string str(locale.length(), 0);
  std::transform(wide.begin(), wide.end(), locale.begin(),
                 [](wchar_t c) { return static_cast<char>(c); });
#else
  auto clocale = getenv("LANGUAGE");
  if (clocale == nullptr) clocale = getenv("LC_ALL");
  if (clocale == nullptr) clocale = getenv("LANG");
  const auto locale = std::string{clocale};
#endif

  return parseLocale(locale);
}
};  // namespace Util

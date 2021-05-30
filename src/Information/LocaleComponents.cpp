// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/LocaleComponents.h"

#include <cassert>

LocaleComponents::LocaleComponents(const std::string& locale) noexcept {
  const auto firstDashIndex = locale.find("-");

  if (firstDashIndex == locale.npos) {
    // Language must be either 2 (ISO 631) or 3 (ISO 631-2) characters wide:
    assert(locale.length() >= 2 && locale.length() <= 3);
    language = locale;
  } else {
    // Language must be either 2 (ISO 631) or 3 (ISO 631-2) characters wide:
    assert(firstDashIndex == 2 || firstDashIndex == 3);
    language = locale.substr(0, firstDashIndex);

    const auto secondDashIndex = locale.find("-", firstDashIndex + 1);
    if (secondDashIndex == locale.npos) {
      // Country must be 2 characters wide:
      assert(locale.length() - firstDashIndex - 1 == 2);
      country = locale.substr(firstDashIndex + 1);
    } else {
      // Script must be 4 characters wide:
      assert(secondDashIndex - firstDashIndex - 1 == 4);
      script = locale.substr(firstDashIndex + 1, 4);

      // Country must be 2 characters wide:
      assert(locale.length() - secondDashIndex - 1 == 2);
      country = locale.substr(secondDashIndex + 1);
    }
  }
}

LocaleComponents::Type LocaleComponents::type() const noexcept {
  const uint8_t noScript = script.empty() ? 0b00 : 0b10;
  const uint8_t noCountry = country.empty() ? 0b00 : 0b01;
  return static_cast<LocaleComponents::Type>(noScript | noCountry);
}

std::string LocaleComponents::string() const noexcept {
  assert(!language.empty());

  switch (type()) {
    case Type::None:
      return language;
    case Type::Country:
      return language + "-" + country;
    case Type::Script:
      return language + "-" + script;
    default:
      return language + "-" + script + "-" + country;
  }
}

bool LocaleComponents::fallback(LocaleComponents& components) const noexcept {
  components.language = language;

  switch (type()) {
    case Type::None:
      return false;
    case Type::Country:
      components.country.clear();
      return true;
    case Type::Script:
      components.script.clear();
      return true;
    default:
      components.country = country;
      components.script.clear();
      return true;
  }
}

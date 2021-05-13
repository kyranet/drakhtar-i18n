// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <array>

/**
 * @brief A numeral system which expresses numbers based on a given set, using
 * digits orr other symbols in a consistent manner.
 *
 * @see https://en.wikipedia.org/wiki/Numeral_system
 */
class ISystem {
  std::array<wchar_t, 10> numbers_;

 public:
  ISystem(wchar_t zero, wchar_t one, wchar_t two, wchar_t three, wchar_t four,
          wchar_t five, wchar_t six, wchar_t seven, wchar_t eight, wchar_t nine)
      : numbers_({zero, one, two, three, four, five, six, seven, eight, nine}) {
  }

  /**
   * @brief Gets the numeral system's character given its value.
   */
  [[nodiscard]] inline wchar_t get(size_t index) const noexcept {
    return numbers_[index];
  }
};

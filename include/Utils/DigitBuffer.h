// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <Information/NumberMetadata.h>

#include <limits>
#include <string>

template <class T>
class DigitBuffer {
  static constexpr size_t DIGITS = std::numeric_limits<T>::digits10 + 1;
  static constexpr size_t U8_DIGITS = DIGITS * 2;

  char buffer[U8_DIGITS]{};
  char* ptr;

 public:
  constexpr DigitBuffer() noexcept { reset(); }

  /**
   * Appends a new digit into the buffer.
   */
  void append(const std::string& digit) noexcept {
    ptr -= digit.length();
#pragma warning(disable : 4996)
    std::strncpy(ptr, digit.c_str(), digit.length());
#pragma warning(default : 4996)
  }

  void append(const NumberMetadata& n, T number) noexcept {
    while (number > 0) {
      append(n.at(number % 10));
      number /= 10;
    }
  }

  constexpr void reset() noexcept {
    ptr = reinterpret_cast<char*>(&buffer) + U8_DIGITS;
  }

  /**
   * Constructs a string from the buffer.
   */
  std::string string() const noexcept { return std::string(ptr); }

  static std::string from(const NumberMetadata& n, T number) noexcept {
    if (number == 0) return n.at(0);

    DigitBuffer<T> db{};
    db.append(n, number);
    return db.string();
  }

  static std::string from(const NumberMetadata* n, T number) noexcept {
    return from(*n, number);
  }
};

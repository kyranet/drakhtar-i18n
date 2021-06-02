// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <cstring>
#include <limits>
#include <string>

#include "Information/NumberMetadata.h"

template <class T>
class DigitBuffer {
  static constexpr size_t DIGITS = std::numeric_limits<T>::digits10 + 1;
  static constexpr size_t U8_DIGITS = DIGITS * 2;

  char buffer_[U8_DIGITS]{};
  char* ptr_;
  size_t length_{0};

 public:
  constexpr DigitBuffer() noexcept { reset(); }

  /**
   * Appends a new digit into the buffer.
   */
  void append(const std::string& digit) noexcept {
    for (auto it = digit.crbegin(); it != digit.crend(); ++it) {
      *--ptr_ = *it;
      ++length_;
    }
  }

  void append(const NumberMetadata& n, T number) noexcept {
    do {
      append(n.at(number % 10));
      number /= 10;
    } while (number > 0);
  }

  constexpr void reset() noexcept {
    ptr_ = reinterpret_cast<char*>(&buffer_) + U8_DIGITS;
  }

  size_t length() const noexcept { return length_; }

  /**
   * Constructs a string from the buffer.
   */
  std::string string() const noexcept { return std::string(ptr_, length()); }

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

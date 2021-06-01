// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <array>
#include <map>
#include <string>

#include "Parser/Strings/StringContent.h"

class NumberMetadata {
 private:
  // punctuation marks symbols:
  std::string decimal_{};
  std::string group_{};
  std::string list_{};
  std::string percentSign_{};
  std::string plusSign_{};
  std::string minusSign_{};
  std::string approximatelySign_{};
  std::string exponential_{};
  std::string superscriptingExponent_{};
  std::string perMille_{};
  std::string infinite_{};
  std::string nan_{};
  std::string timeSeparator_{};

  std::array<std::string, 10> numbers_{};

  static bool read(const std::map<std::string, StringContent>& map,
                   const std::string& key, std::string& string) noexcept;

 public:
  NumberMetadata(const std::map<std::string, StringContent>& map);

  void apply(const std::map<std::string, StringContent>& map) noexcept;

  /**
   * Gets the 'decimal' symbol.
   */
  [[nodiscard]] const std::string& decimal() const noexcept { return decimal_; }

  /**
   * Gets the 'group separator' symbol.
   */
  [[nodiscard]] const std::string& group() const noexcept { return group_; }

  /**
   * Gets the 'list' symbol.
   */
  [[nodiscard]] const std::string& list() const noexcept { return list_; }

  /**
   * Gets the 'percentSign' symbol.
   */
  [[nodiscard]] const std::string& percent() const noexcept {
    return percentSign_;
  }

  /**
   * Gets the 'plusSign' symbol.
   */
  [[nodiscard]] const std::string& plus() const noexcept { return plusSign_; }

  /**
   * Gets the 'minusSign' symbol.
   */
  [[nodiscard]] const std::string& minus() const noexcept { return minusSign_; }

  /**
   * Gets the 'approximatelySign' symbol.
   */
  [[nodiscard]] const std::string& approximately() const noexcept {
    return approximatelySign_;
  }

  /**
   * Gets the 'exponential' symbol.
   */
  [[nodiscard]] const std::string& exponential() const noexcept {
    return exponential_;
  }

  /**
   * Gets the 'superscriptingExponent' symbol.
   */
  [[nodiscard]] const std::string& superscriptingExponent() const noexcept {
    return superscriptingExponent_;
  }

  /**
   * Gets the 'perMille' symbol.
   */
  [[nodiscard]] const std::string& perMille() const noexcept {
    return perMille_;
  }

  /**
   * Gets the 'infinity' symbol.
   */
  [[nodiscard]] const std::string& infinity() const noexcept {
    return infinite_;
  }

  /**
   * Gets the 'nan' symbol.
   */
  [[nodiscard]] const std::string& nan() const noexcept { return nan_; }

  /**
   * Gets the 'timeSeparator' symbol.
   */
  [[nodiscard]] const std::string& timeSeparator() const noexcept {
    return timeSeparator_;
  }

  /**
   * Gets the character for the given number, between 0 and 9.
   */
  [[nodiscard]] const std::string& at(size_t index) const noexcept {
    return numbers_[index];
  }
};

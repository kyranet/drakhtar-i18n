// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

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
  std::string infinity_{};
  std::string nan_{};
  std::string timeSeparator_{};

  // numeric digits symbols:
  std::string zero_{};
  std::string one_{};
  std::string two_{};
  std::string three_{};
  std::string four_{};
  std::string five_{};
  std::string six_{};
  std::string seven_{};
  std::string eight_{};
  std::string nine_{};

 public:
  NumberMetadata(std::map<std::string, StringContent> map);

  // ******************
  // PUNCTUATION MARKS:
  // ******************

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
    return infinity_;
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

  // ***************
  // NUMERIC DIGITS:
  // ***************

  /**
   * Gets the 'zero' symbol.
   */
  [[nodiscard]] const std::string& zero() const noexcept { return zero_; }

  /**
   * Gets the 'one' symbol.
   */
  [[nodiscard]] const std::string& one() const noexcept { return one_; }

  /**
   * Gets the 'two' symbol.
   */
  [[nodiscard]] const std::string& two() const noexcept { return two_; }

  /**
   * Gets the 'three' symbol.
   */
  [[nodiscard]] const std::string& three() const noexcept { return three_; }

  /**
   * Gets the 'four' symbol.
   */
  [[nodiscard]] const std::string& four() const noexcept { return four_; }

  /**
   * Gets the 'five' symbol.
   */
  [[nodiscard]] const std::string& five() const noexcept { return five_; }

  /**
   * Gets the 'six' symbol.
   */
  [[nodiscard]] const std::string& six() const noexcept { return six_; }

  /**
   * Gets the 'seven' symbol.
   */
  [[nodiscard]] const std::string& seven() const noexcept { return seven_; }

  /**
   * Gets the 'eight' symbol.
   */
  [[nodiscard]] const std::string& eight() const noexcept { return eight_; }

  /**
   * Gets the 'nine' symbol.
   */
  [[nodiscard]] const std::string& nine() const noexcept { return nine_; }
};

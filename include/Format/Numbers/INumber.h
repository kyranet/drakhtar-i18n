// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

class INumber {
 private:
  std::string name_{};
  std::string decimal_{};
  std::string group_{};
  std::string percentSign_{};
  std::string plusSign_{};
  std::string minusSign_{};
  std::string exponential_{};

 public:
  [[nodiscard]] inline const std::string& name() const noexcept {
    return name_;
  }
  inline std::string& name() noexcept { return name_; }

  [[nodiscard]] inline const std::string& decimal() const noexcept {
    return decimal_;
  }
  inline std::string& decimal() noexcept { return decimal_; }

  [[nodiscard]] inline const std::string& group() const noexcept {
    return group_;
  }
  inline std::string& group() noexcept { return group_; }

  [[nodiscard]] inline const std::string& percentSign() const noexcept {
    return percentSign_;
  }
  inline std::string& percentSign() noexcept { return percentSign_; }

  [[nodiscard]] inline const std::string& plusSign() const noexcept {
    return plusSign_;
  }
  inline std::string& plusSign() noexcept { return plusSign_; }

  [[nodiscard]] inline const std::string& minusSign() const noexcept {
    return minusSign_;
  }
  inline std::string& minusSign() noexcept { return minusSign_; }

  [[nodiscard]] inline const std::string& exponential() const noexcept {
    return exponential_;
  }
  inline std::string& exponential() noexcept { return exponential_; }

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(int32_t value) const = 0;

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(uint32_t value) const = 0;

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(int64_t value) const = 0;

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(uint64_t value) const = 0;

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(float value) const = 0;

  /**
   * @brief Formats the number given in the parameter using the number's system.
   */
  virtual std::string format(double value) const = 0;
};

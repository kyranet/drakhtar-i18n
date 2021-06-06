// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/Locale.h"

#include <cassert>
#include <cmath>
#include <cstdarg>
#include <stack>

#include "Information/LocaleComponents.h"
#include "Information/NumberMetadata.h"
#include "LocaleManager.h"
#include "Parser/FileParser.h"
#include "Parser/Strings/StringContent.h"
#include "Utils/DigitBuffer.h"

void Locale::init(const std::string& locale) {
  locale_ = locale;

  std::filesystem::path root{"languages"};
  loadMetadata(root / locale);
}

void Locale::load(const std::filesystem::path& path,
                  const std::string& prefix) {
  for (auto& file : std::filesystem::directory_iterator(path)) {
    const auto name = file.path().filename().string();

    // If the file is prefixed with a dot, skip:
    if (name[0] == '.') continue;

    // If the entry is a directory, load recursively:
    if (file.is_directory()) {
      load(file.path(), prefix.empty() ? name + "/" : prefix + name + "/");
      continue;
    }

    // If the file is a regular file, skip:
    if (!file.is_regular_file()) {
      continue;
    }

    // If the file is .txt file, read it and store its key/value pairs:
    if (file.path().extension().string() == ".txt") {
      std::ifstream s{file.path()};
      FileParser fp{s};
      for (const auto& pair : fp.run()) {
        const auto key = prefix + pair.first;
        keys_.insert({key, pair.second});
      }
      continue;
    }

    // If the file is anything else, save it as an asset:
    assets_.insert({prefix + name, file.path().string()});
  }
}

void Locale::loadMetadata(const std::filesystem::path& path) {
  std::ifstream s{path / ".meta.txt"};
  FileParser fp{s};
  const auto map = fp.run();
  name_ = map.at("NAME").run({});

  numeric_ = new NumberMetadata{map};
}

bool Locale::loadFallback(const std::string& name) {
  // If the manager doesn't have the locale folder, skip:
  if (!manager_.has(name)) {
    return false;
  }

  // If the locale isn't loaded, load, and if it fails, skip:
  if (!manager_.loaded(name) && !manager_.load(name)) {
    return false;
  }

  // For each of the fallback's keys, insert them to this object:
  const auto& l = manager_.get(name);
  for (const auto& pair : l.keys_) {
    keys_.insert(pair);
  }

  return true;
}

void Locale::loadFallbacks() {
  // Load the nearest parent (ja-Kata-JP -> ja-JP -> ja) as fallback:
  LocaleComponents fb{locale_};
  while (fb.fallback() && !loadFallback(fb.string()))
    ;
}

void Locale::load() {
  std::filesystem::path root{"languages"};
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  root.append(locale());
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  loadFallbacks();
  load(root, "");
}

const std::string& Locale::display(const std::string& arg) const { return arg; }

std::string Locale::display(const char* arg) const { return std::string(arg); }

std::string Locale::display(bool arg) const {
  // TODO: Implement method with locale-aware values.
  return arg ? "true" : "false";
}

std::string Locale::display(int8_t arg) const {
  return arg < 0 ? numbers()->minus() + display(static_cast<uint8_t>(-arg))
                 : display(static_cast<uint8_t>(arg));
}

std::string Locale::display(int16_t arg) const {
  return arg < 0 ? numbers()->minus() + display(static_cast<uint16_t>(-arg))
                 : display(static_cast<uint16_t>(arg));
}

std::string Locale::display(int32_t arg) const {
  return arg < 0 ? numbers()->minus() + display(static_cast<uint32_t>(-arg))
                 : display(static_cast<uint32_t>(arg));
}

std::string Locale::display(int64_t arg) const {
  return arg < 0 ? numbers()->minus() + display(static_cast<uint64_t>(-arg))
                 : display(static_cast<uint64_t>(arg));
}

std::string Locale::display(uint8_t arg) const {
  const auto& n = *numbers();

  // If single digit, return single at:
  if (arg < 10) return n.at(arg);

  // If two digits, return at for the first digit, and at for the second:
  if (arg < 100) return n.at(arg / 10) + n.at(arg % 10);

  // Else, since maximum is 255, return at for each of 3 digits:
  return n.at(arg / 100) + n.at((arg / 10) % 10) + n.at(arg % 10);
}

std::string Locale::display(uint16_t arg) const {
  return DigitBuffer<uint16_t>::from(numbers(), arg);
}

std::string Locale::display(uint32_t arg) const {
  return DigitBuffer<uint32_t>::from(numbers(), arg);
}

std::string Locale::display(uint64_t arg) const {
  return DigitBuffer<uint64_t>::from(numbers(), arg);
}

std::string Locale::display(float arg) const {
  return display(static_cast<double>(arg));
}

std::string Locale::display(double arg) const {
  const auto& n = *numbers();
  const auto c = std::fpclassify(arg);

  // If the classification is NaN, return early:
  if (c == FP_NAN) return n.nan();

  // Get the sign bit, if 1, it's negative, otherwise positive:
  const auto negative = std::signbit(arg) == 1;

  // If the classification is 0, print -0 or 0:
  if (c == FP_ZERO) {
    return negative ? n.minus() + n.at(0) : n.at(0);
  }

  // If the classification is Infinite, print -∞ or +∞:
  if (c == FP_INFINITE) {
    return negative ? n.minus() + n.infinity() : n.plus() + n.infinity();
  }

  // If the classification is Normal, print the double as a normal number:
  if (c == FP_NORMAL) {
    return negative ? n.minus() + displayMaybeExponent(-arg)
                    : displayMaybeExponent(arg);
  }

  // If the classification is Denormal, extract the exponent,
  // normalise the number, and then print as a normal number:
  return negative ? n.minus() + displayMaybeExponent(-arg)
                  : displayMaybeExponent(arg);
}

std::string Locale::displayMaybeExponent(double arg) const {
  const auto exponent = static_cast<int32_t>(std::log10(arg));
  if (std::abs(exponent) >= static_cast<int32_t>(displayDigits()))
    return displayExponent(arg, exponent);
  return displayNormal(arg);
}

std::string Locale::displayExponent(double arg, int32_t exponent) const {
  const auto& n = *numbers();

  const auto normalized = arg * std::pow(10.0, static_cast<double>(-exponent));
  const auto number = displayNormal(normalized);
  const auto exp =
      exponent < 0 ? display(exponent) : n.plus() + display(exponent);

  return number + n.exponential() + exp;
}

std::string Locale::displayNormal(double arg) const {
  const auto& n = *numbers();
  double integral;
  auto decimal = std::modf(arg, &integral);

  const auto w =
      DigitBuffer<uint64_t>::from(n, static_cast<uint64_t>(integral));
  if (decimal == 0.0) return w;

  std::stringstream ss{};
  ss << w;
  ss << n.decimal();

  uint32_t added{0};
  double digit;
  do {
    decimal = std::modf(decimal * 10.0, &digit);
    ss << n.at(static_cast<size_t>(digit));
  } while (decimal != 0.0 && ++added < displayDigits());

  return ss.str();
}

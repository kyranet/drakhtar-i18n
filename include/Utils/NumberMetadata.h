// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <algorithm>
#include <string>

// the type of numeric system language
enum class numberSystem { latn };
using nSys = numberSystem;

class NumberMetadata {
 private:
  // nSys lan_system;
  std::string decimal;
  std::string group;
  std::string list;
  std::string percentSign;
  std::string plusSign;
  std::string minusSign;
  std::string approximatelySign;
  std::string exponential;
  std::string superscriptingExponent;
  std::string perMille;
  std::string infinity;
  std::string nan;
  std::string timeSeparator;

 public:
  NumericMetadata(size_t number, numberSystem system) { analice(number); };

 private:
  void analice(size_t number);
};

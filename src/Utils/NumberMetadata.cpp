// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Utils/NumberMetadata.h"

#include "Information/Locale.h"

NumberMetadata::NumberMetadata(std::map<std::string, StringContent> map) {
  // data map assignation values

  // punctuation marks symbols:
  decimal_ = map.at("DECIMAL").run({});
  group_ = map.at("GROUP").run({});
  list_ = map.at("LIST").run({});
  percentSign_ = map.at("PERCENT").run({});
  plusSign_ = map.at("PLUS").run({});
  minusSign_ = map.at("MINUS").run({});
  approximatelySign_ = map.at("APPROXIMATELY").run({});
  exponential_ = map.at("EXPONENTIAL").run({});
  superscriptingExponent_ = map.at("SUPER_SCRIPTING_EXPONENT").run({});
  perMille_ = map.at("PER_MILLE").run({});
  infinite_ = map.at("INFINITILY").run({});
  nan_ = map.at("NAN").run({});
  timeSeparator_ = map.at("TIME_SEPARATOR").run({});

  // numeric digits symbols:
  zero_ = map.at("ZERO").run({});
  one_ = map.at("ONE").run({});
  two_ = map.at("TWO").run({});
  three_ = map.at("THREE").run({});
  four_ = map.at("FOUR").run({});
  five_ = map.at("FIVE").run({});
  six_ = map.at("SIX").run({});
  seven_ = map.at("SEVEN").run({});
  eight_ = map.at("EIGHT").run({});
  nine_ = map.at("NINE").run({});
}

// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/NumberMetadata.h"

#include "Information/Locale.h"
#include "Parser/FileParser.h"
#include "Parser/Strings/StringContent.h"
#include "Utils/Util.h"

NumberMetadata::NumberMetadata(
    const std::map<std::string, StringContent>& map) {
  std::string numeric;
  if (read(map, "NUMERIC_SYSTEM", numeric)) {
    std::filesystem::path path{"languages"};
    path.append(".numeric");
    path.append(numeric + ".txt");

    assert(std::filesystem::exists(path));

    std::ifstream s;
    s.open(path, std::ios_base::binary | std::ios_base::in);
    apply(FileParser(s).run());
  }

  apply(map);
}

void NumberMetadata::apply(
    const std::map<std::string, StringContent>& map) noexcept {
  // Punctuation marks:
  read(map, "DECIMAL", decimal_);
  read(map, "GROUP", group_);
  read(map, "LIST", list_);
  read(map, "PERCENT", percentSign_);
  read(map, "PLUS", plusSign_);
  read(map, "MINUS", minusSign_);
  read(map, "APPROXIMATELY", approximatelySign_);
  read(map, "EXPONENTIAL", exponential_);
  read(map, "SUPER_SCRIPTING_EXPONENT", superscriptingExponent_);
  read(map, "PER_MILLE", perMille_);
  read(map, "INFINITE", infinite_);
  read(map, "NAN", nan_);
  read(map, "TIME_SEPARATOR", timeSeparator_);

  // Digits:
  read(map, "ZERO", numbers_[0]);
  read(map, "ONE", numbers_[1]);
  read(map, "TWO", numbers_[2]);
  read(map, "THREE", numbers_[3]);
  read(map, "FOUR", numbers_[4]);
  read(map, "FIVE", numbers_[5]);
  read(map, "SIX", numbers_[6]);
  read(map, "SEVEN", numbers_[7]);
  read(map, "EIGHT", numbers_[8]);
  read(map, "NINE", numbers_[9]);
}

bool NumberMetadata::read(const std::map<std::string, StringContent>& map,
                          const std::string& key,
                          std::string& string) noexcept {
  const auto it = map.find(key);
  if (it == map.cend()) return false;

  string = it->second.run({});
  return true;
}

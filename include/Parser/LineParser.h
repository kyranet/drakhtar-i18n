// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <stdexcept>
#include <string>

#include "Parser/IParser.h"
#include "Parser/Strings/StringContent.h"

class LineParser : public IParser<std::pair<std::string, StringContent>> {
 public:
  std::string key;
  StringContent value;

  LineParser(Tokenizer t) : IParser(t){};
  std::pair<std::string, StringContent> run() override;

  StringContent parseValue();
};

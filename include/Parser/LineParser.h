// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

#include "Parser/IParser.h"
#include "Parser/Strings/StringContent.h"

class LineParser : public IParser<std::pair<std::string, StringContent>> {
  StringContent parseValue();

 public:
  LineParser(Tokenizer& t) : IParser(t){};
  LineParser(std::istream& stream) : IParser(stream) {}
  std::pair<std::string, StringContent> run() override;
};

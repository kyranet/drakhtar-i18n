// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Parser/IParser.h"
#include "Parser/Tokenizer.h"

class StringContent;

class StringParser : public IParser<StringContent> {
  std::string parseEscape();
  std::string parseOctal(char first);
  std::string parseHexadecimal();
  std::string parseUnicode();
  size_t parseVariable();

 public:
  StringContent run() override;
};

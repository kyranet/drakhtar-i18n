// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <vector>

#include "Parser/IParser.h"
#include "Parser/Tokenizer.h"

class StringContent;

class StringParser : public IParser<StringContent> {
  std::string parseEscape();
  std::string parseOctal(char first);
  std::string parseHexadecimal();
  std::string parseHexadecimal(size_t size);
  std::string parseUnicode();
  size_t parseVariable();
  std::vector<std::string> parseModifiers();

 public:
  StringParser(std::istream& stream) : IParser(stream) {}
  StringParser(Tokenizer t) : IParser(t) {}
  StringContent run() override;
};

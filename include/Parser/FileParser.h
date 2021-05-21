// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "Parser/IParser.h"
#include "Parser/Strings/StringContent.h"

class FileParser : public IParser<std::map<std::string, StringContent>> {
  std::map<std::string, StringContent> map_;

 public:
  FileParser(std::istream& stream) : IParser(stream){};
  std::map<std::string, StringContent> run() override;
};

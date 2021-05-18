// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

#include "Parser/IParser.h"

class LineParser : public IParser {
 public:
  std::string key;
  std::string value;

  std::string tempVariables[3] = {"Drakhtar", "Thassa", "Valar"};

  LineParser(std::string line);
  std::string parseVariables(std::string line);
  std::string parseNewLines(std::string line);
};

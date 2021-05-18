// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>

#include "Parser/IParser.h"

class LineParser : public IParser {
 public
  std::string key;
 public
  std::string value;

  LineParser(std::string line);
};

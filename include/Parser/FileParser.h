// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <fstream>
#include <map>
#include <string>

#include "Parser/IParser.h"
#include "Parser/LineParser.h"

class FileParser : public IParser {
  std::map<std::string, std::string> map_;

  FileParser(std::string file);
};

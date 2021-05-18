#include "FileParser.h"

#include <iostream>

FileParser::FileParser(std::string file) {
  std::ifstream infile(file);

  std::string line;
  while (std::getline(infile, line)) {
    LineParser lp = LineParser(line);
    map_.insert(std::pair<std::string, std::string>(lp.key, lp.value));
  }
}
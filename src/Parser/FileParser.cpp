#include "Parser/FileParser.h"

FileParser::FileParser(std::string file) {
  std::ifstream infile(file);

  std::string line;
  while (std::getline(infile, line)) {
    LineParser lp(line);
    map_.insert(line.key, line.value);
  }
}
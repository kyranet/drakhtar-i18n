#include "Parser/LineParser.h"

LineParser::LineParser(std::string line) {
  size_t separator = line.find("=");
  key = line.substr(0, separator);
  value = line.substr(separator, line.size());
}
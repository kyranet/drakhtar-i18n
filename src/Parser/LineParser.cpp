#include "Parser/LineParser.h"

LineParser::LineParser(std::string line) {
  line = parseVariables(line);
  line = parseNewLines(line);
  size_t separator = line.find("=");
  key = line.substr(0, separator);
  value = line.substr(separator + 1, line.size());
}

std::string LineParser::parseVariables(std::string line) {
  size_t startIndex = 0;
  size_t endIndex = 0;

  while (startIndex != -1) {
    startIndex = line.find("{", startIndex);
    endIndex = line.find("}", endIndex);
    if (startIndex != -1 && endIndex != -1) {
      int key = std::atoi(line.substr(startIndex + 1, endIndex).c_str());
      // TODO: Read keys from somewhere else
      line.replace(startIndex, endIndex - startIndex + 1, tempVariables[key]);
    }
  }

  return line;
}

std::string LineParser::parseNewLines(std::string line) {
  size_t startIndex = 0;
  while (startIndex != -1) {
    startIndex = line.find("\\n", startIndex);
    if (startIndex != -1) {
      line.erase(startIndex, 2);
      line.insert(startIndex, 1, '\n');
    }
  }

  return line;
}

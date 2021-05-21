#include "Parser/LineParser.h"

#include <sstream>

#include "Parser/CommentParser.h"
#include "Parser/Strings/StringParser.h"
#include "Utils/Util.h"

std::pair<std::string, StringContent> LineParser::run() {
  std::stringstream ss{key};
  auto& t = tokenizer();

  while (!t.finished()) {
    const auto c = t.next();

    if (Util::isValidIdentifierLetter(c))
      ss << c;
    else if (c == '#')
      CommentParser(t).run();
    else if (c == '=') {
      key = ss.str();
      value = parseValue();

      return std::pair<std::string, StringContent>(key, value);
    } else {
      std::ostringstream msg;
      msg << "Unexpected character '" << c << "' while reading an identifier.";
      throw std::runtime_error(msg.str());
    }
  }

  throw std::runtime_error("Unexpected end of input.");
}

StringContent LineParser::parseValue() {
  auto& t = tokenizer();
  if (t.finished()) throw std::runtime_error("Unexpected end of input.");

  const auto c = t.next();
  if (c == '"') return StringParser(t).run();

  std::ostringstream msg;
  msg << "Unexpected character '" << c << "' while reading a value.";
  throw std::runtime_error(msg.str());
}

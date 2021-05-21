#include "Parser/LineParser.h"

#include <sstream>

#include "Parser/CommentParser.h"
#include "Parser/Strings/StringParser.h"
#include "Utils/Util.h"

std::pair<std::string, StringContent> LineParser::run() {
  std::stringstream ss{};
  auto& t = tokenizer();

  while (true) {
    const auto c = t.next();
    if (t.finished()) break;

    if (Util::isValidIdentifierLetter(c)) {
      ss << c;
    } else if (c == '#') {
      if (ss.rdbuf()->in_avail()) {
        throw std::runtime_error("Unexpected comment after '" + ss.str() +
                                 "'.");
      }

      CommentParser(t).run();
      if (t.finished()) break;
    } else if (c == '=') {
      return {ss.str(), parseValue()};
    } else {
      unexpectedCharacter(c, "an identifier");
    }
  }

  unexpectedEndOfInput();
}

StringContent LineParser::parseValue() {
  auto& t = tokenizer();

  const auto c = t.next();
  if (t.finished()) unexpectedEndOfInput();
  if (c == '"') return StringParser(t).run();

  unexpectedCharacter(c, "a value");
}

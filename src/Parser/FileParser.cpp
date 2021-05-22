#include "Parser/FileParser.h"

#include <iostream>

#include "Parser/CommentParser.h"
#include "Parser/LineParser.h"
#include "Parser/Tokenizer.h"
#include "Utils/Util.h"

std::map<std::string, StringContent> FileParser::run() {
  std::stringstream ss{};
  auto& t = tokenizer();

  char c;
  while (t.next(c)) {
    // If the character is a whitespace or a line break, continue:
    if (Util::isWhiteSpace(c) || Util::isLineBreak(c)) {
      continue;
    }

    // If the character is a comment, consume it:
    if (c == '#') {
      CommentParser(t).run();
      if (t.finished()) break;
    } else {
      t.undo();
      map_.insert(LineParser(t).run());
      if (t.finished()) break;
    }
  }

  return map_;
}

#include "Parser/CommentParser.h"

void CommentParser::run() {
  auto& t = tokenizer();

  while (true) {
    const auto c = t.next();
    if (t.finished()) break;
    if (c == '\n') break;
  }
}

#include "Parser/CommentParser.h"

void CommentParser::run() {
  auto& t = tokenizer();
  while (!t.finished()) {
    const auto c = t.next();
    if (c == '\n') break;
  }
}
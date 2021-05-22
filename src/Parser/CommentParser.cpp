#include "Parser/CommentParser.h"

void CommentParser::run() {
  auto& t = tokenizer();

  char c;
  while (t.next(c)) {
    if (c == '\n') break;
  }
}

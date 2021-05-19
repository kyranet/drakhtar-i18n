#include "Parser/FileParser.h"

#include <iostream>

#include "Parser/CommentParser.h"
#include "Parser/LineParser.h"
#include "Parser/Tokenizer.h"

std::map<std::string, StringContent> FileParser::run() {
  std::stringstream ss{};
  auto& t = tokenizer();

  while (!t.finished()) {
    const auto c = t.next();
    if (c == '#')
      CommentParser(t).run();
    else if (c == '\n')
      continue;
    else {
      t.undo();
      auto entry = LineParser(t);
      map_.insert(entry.run());
      t.next();
    }
  }

  return map_;
}

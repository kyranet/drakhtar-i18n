// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Parser/IParser.h"

class CommentParser : public IParser<void> {
 public:
  CommentParser(Tokenizer t) : IParser(t){};
  void run() override;
};

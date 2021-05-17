// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Parser/IParser.h"
#include "Parser/Tokenizer.h"

class StringContent;

class StringParser : public IParser<StringContent> {
 public:
  StringContent run() override;
};

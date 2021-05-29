// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Parser/Strings/StringContent.h"

#include <cassert>
#include <sstream>

#include "Format/Strings/TransformerManager.h"

std::string StringContent::run(std::vector<std::string> variables) const {
  if (empty()) return "";
  if (!dynamic()) return parts_[0].content();

  std::stringstream ss{};
  for (const auto& part : parts_) {
    if (part.isContent()) {
      ss << part.content();
    } else {
      assert(part.variable() < variables.size());
      std::string s = variables[part.variable()];
      auto& modifiers = modifiers_[part.variable()];
      for (const auto& t : modifiers)
        s = TransformerManager::getInstance().format(s, t);
      ss << s;
    }
  }

  return ss.str();
}

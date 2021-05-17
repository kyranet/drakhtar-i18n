// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Parser/Strings/StringContent.h"

#include <cassert>
#include <sstream>

std::string StringContent::run(std::vector<std::string> variables) const {
  if (empty()) return "";
  if (!dynamic()) return parts_[0].content();

  std::stringstream ss{};
  for (const auto& part : parts_) {
    if (part.type == PartType::Content) {
      ss << part.content();
    } else {
      assert(part.variable() < variables.size());
      ss << variables[part.variable()];
    }
  }

  return ss.str();
}

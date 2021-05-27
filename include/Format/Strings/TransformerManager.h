// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <stdexcept>
#include <string>

#include "ITransformer.h"
#include "UppercaseTransformer.h"

class TransformerManager {
  static TransformerManager* instance_;
  static std::map<std::string, ITransformer*> transformers;

  TransformerManager() = default;
  ~TransformerManager() = default;

  static void init();

 public:
  static TransformerManager& getInstance();

  std::string format(std::string string, std::string format) {
    const auto search = transformers.find(format);
    if (search != transformers.cend()) return search->second->format(string);

    throw std::runtime_error("Unexpected format '" + format + "'.");
  }
};
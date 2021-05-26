// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>

#include "ITransformer.h"
#include "UppercaseTransformer.h"

class TransformerManager {
  static TransformerManager* instance_;
  static std::map<std::string, ITransformer*> transformers;

  TransformerManager() = default;
  ~TransformerManager() = default;

  static void init() {
    transformers.insert(std::pair<std::string, ITransformer*>(
        "uppercase", new UppercaseTransformer()));
  }

 public:
  static TransformerManager& getInstance() {
    if (instance_ == nullptr) {
      instance_ = new TransformerManager();
      init();
    }

    return *instance_;
  }

  std::string format(std::string string, std::string format) {
    return transformers[format]->format(string);
  }
};
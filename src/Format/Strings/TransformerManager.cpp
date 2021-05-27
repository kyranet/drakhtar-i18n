#include "Format/Strings/TransformerManager.h"

#include "Format/Strings/LowercaseTransformer.h"
#include "Format/Strings/UppercaseTransformer.h"

TransformerManager* TransformerManager::instance_ = nullptr;
std::map<std::string, ITransformer*> TransformerManager::transformers;

void TransformerManager::init() {
  transformers.insert(std::pair<std::string, ITransformer*>(
      "uppercase", new UppercaseTransformer()));
  transformers.insert(std::pair<std::string, ITransformer*>(
      "lowercase", new LowercaseTransformer()));
}

TransformerManager& TransformerManager::getInstance() {
  if (instance_ == nullptr) {
    instance_ = new TransformerManager();
    init();
  }

  return *instance_;
}
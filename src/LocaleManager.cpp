// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "LocaleManager.h"

#include <cassert>
#include <filesystem>

#include "Utils/Util.h"

void LocaleManager::init() {
  load(true);
  initialized_ = true;
}

int32_t LocaleManager::load(bool metadataOnly) {
  assert(std::filesystem::exists("languages"));
  assert(std::filesystem::is_directory("languages"));

  // Iterate over the entire languages directory:
  int32_t loaded{0};
  for (auto& file : std::filesystem::directory_iterator("languages")) {
    // If the entry is not a directory, skip:
    if (!file.is_directory()) {
      continue;
    }

    // If the entry does not contain a .meta.txt file, skip:
    if (!std::filesystem::exists(file.path() / ".meta.txt")) {
      continue;
    }

    // Load the directory:
    const auto locale = file.path().filename().string();
    if (load(locale, metadataOnly)) {
      ++loaded;
    }
  }

  return loaded;
}

bool LocaleManager::load(const std::string& locale, bool metadataOnly) {
  std::filesystem::path path{"languages"};

  assert(std::filesystem::exists(path));
  assert(std::filesystem::is_directory(path));

  path.append(locale);
  if (!std::filesystem::exists(path)) return false;

  const auto meta = path / ".meta.txt";
  if (!std::filesystem::exists(meta)) return false;

  Locale l{};
  l.init(locale);

  names_.insert({l.locale(), l.name()});

  if (!metadataOnly) {
    l.load();
    loaded_.insert({locale, l});
  }

  return true;
}

int32_t LocaleManager::load() { return load(false); }

bool LocaleManager::load(const std::string& locale) {
  return load(locale, false);
}

static Util::Locale getPreferred() noexcept { return Util::getLocale(); }

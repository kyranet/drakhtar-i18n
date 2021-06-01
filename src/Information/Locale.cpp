// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/Locale.h"

#include <cassert>
#include <cstdarg>
#include <stack>

#include "Information/LocaleComponents.h"
#include "Information/NumberMetadata.h"
#include "LocaleManager.h"
#include "Parser/FileParser.h"
#include "Parser/Strings/StringContent.h"

void Locale::init(const std::string& locale) {
  locale_ = locale;

  std::filesystem::path root{"languages"};
  loadMetadata(root / locale);
}

void Locale::load(const std::filesystem::path& path,
                  const std::string& prefix) {
  for (auto& file : std::filesystem::directory_iterator(path)) {
    const auto name = file.path().filename().string();

    // If the file is prefixed with a dot, skip:
    if (name[0] == '.') continue;

    // If the entry is a directory, load recursively:
    if (file.is_directory()) {
      load(file.path(), prefix.empty() ? name + "/" : prefix + name + "/");
      continue;
    }

    // If the file is a regular file, skip:
    if (!file.is_regular_file()) {
      continue;
    }

    // If the file is .txt file, read it and store its key/value pairs:
    if (file.path().extension().string() == ".txt") {
      std::ifstream s{file.path()};
      FileParser fp{s};
      for (const auto& pair : fp.run()) {
        const auto key = prefix + pair.first;
        keys_.insert({key, pair.second});
      }
      continue;
    }

    // If the file is anything else, save it as an asset:
    assets_.insert({prefix + name, file.path().string()});
  }
}

void Locale::loadMetadata(const std::filesystem::path& path) {
  std::ifstream s{path / ".meta.txt"};
  FileParser fp{s};
  const auto map = fp.run();
  name_ = map.at("NAME").run({});

  // TODO(Pablo): Assign all other properties here
  numeric_ = new NumberMetadata{map};
}

bool Locale::loadFallback(const std::string& name) {
  // If the manager doesn't have the locale folder, skip:
  if (!manager_.has(name)) {
    return false;
  }

  // If the locale isn't loaded, load, and if it fails, skip:
  if (!manager_.loaded(name) && !manager_.load(name)) {
    return false;
  }

  // For each of the fallback's keys, insert them to this object:
  const auto& l = manager_.get(name);
  for (const auto& pair : l.keys_) {
    keys_.insert(pair);
  }

  return true;
}

void Locale::loadFallbacks() {
  // Load the nearest parent (ja-Kata-JP -> ja-JP -> ja) as fallback:
  LocaleComponents fb{locale_};
  while (fb.fallback() && !loadFallback(fb.string()))
    ;
}

void Locale::load() {
  std::filesystem::path root{"languages"};
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  root.append(locale());
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  loadFallbacks();
  load(root, "");
}

const std::string& Locale::display(const std::string& arg) const { return arg; }

std::string Locale::display(const char* arg) const { return std::string(arg); }

std::string Locale::display(bool arg) const {
  // TODO: Implement method.
  (void)arg;

  return "false";
}

std::string Locale::display(int8_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "-1";
}

std::string Locale::display(int16_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "-1";
}

std::string Locale::display(int32_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "-1";
}

std::string Locale::display(int64_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "-1";
}

std::string Locale::display(uint8_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0";
}

std::string Locale::display(uint16_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0";
}

std::string Locale::display(uint32_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0";
}

std::string Locale::display(uint64_t arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0";
}

std::string Locale::display(float arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0.0";
}

std::string Locale::display(double arg) const {
  // TODO: Implement method.
  (void)arg;

  return "0.0";
}
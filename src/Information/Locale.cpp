// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/Locale.h"

#include "Parser/FileParser.h"
#include <cassert>
#include <stack>
#include "Parser/Strings/StringContent.h"

#include "Information/LocaleComponents.h"
#include "LocaleManager.h"
#include "Parser/FileParser.h"

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

    if (!file.is_regular_file()) {
      continue;
    }

    std::ifstream s{file.path()};
    FileParser fp{s};
    for (const auto& pair : fp.run()) {
      const auto key = prefix + pair.first;
      keys_.insert({key, pair.second});
    }
    }
  }

void Locale::loadMetadata(const std::filesystem::path& path) {
  std::ifstream s{path / ".meta.txt"};
  FileParser fp{s};
  const auto map = fp.run();
  name_ = map.at("NAME").run({});

  // TODO(Pablo): Assign all other properties here
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

std::string Locale::format(const std::string& arg...) {
  va_list args;
  va_start(args, arg);
  auto& key = arg;

  // TODO: Omar's part, get the real content using key.
  StringContent content{};

  std::vector<std::string> argsFormat{};

  for (const auto type : content.types()) {
    switch (type) {
    case StringContent::Type::String:
      argsFormat.push_back(va_arg(args, std::string));
      break;
    case StringContent::Type::Boolean:
      argsFormat.push_back(display(va_arg(args, bool)));
      break;
    case StringContent::Type::Int8:
      argsFormat.push_back(display(va_arg(args, int8_t)));
      break;
    case StringContent::Type::Int16:
      argsFormat.push_back(display(va_arg(args, int16_t)));
      break;
    case StringContent::Type::Int32:
      argsFormat.push_back(display(va_arg(args, int32_t)));
      break;
    case StringContent::Type::Int64:
      argsFormat.push_back(display(va_arg(args, int64_t)));
      break;
    case StringContent::Type::UInt8:
      argsFormat.push_back(display(va_arg(args, uint8_t)));
      break;
    case StringContent::Type::UInt16:
      argsFormat.push_back(display(va_arg(args, uint16_t)));
      break;
    case StringContent::Type::UInt32:
      argsFormat.push_back(display(va_arg(args, uint32_t)));
      break;
    case StringContent::Type::UInt64:
      argsFormat.push_back(display(va_arg(args, uint32_t)));
      break;
    case StringContent::Type::Float32:
      argsFormat.push_back(display(va_arg(args, float)));
      break;
    case StringContent::Type::Float64:
      argsFormat.push_back(display(va_arg(args, double)));
      break;
    default:
      // MALO, ESO NO SE HACE
      break;

      return content.run(argsFormat);
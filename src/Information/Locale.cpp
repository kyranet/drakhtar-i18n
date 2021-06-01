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

/*
std::string Locale::format(const std::string* arg...) {
  va_list args;
  va_start(args, arg);
  auto& key = arg;

  const auto& content = keys_.at(*key);

  std::vector<std::string> formatted{};

  for (const auto type : content.types()) {
    switch (type) {
      case Type::String:
        formatted.push_back(va_arg(args, std::string));
        break;
      case Type::Boolean:
        formatted.push_back(display(va_arg(args, bool)));
        break;
      case Type::Int8:
        formatted.push_back(display(va_arg(args, int8_t)));
        break;
      case Type::Int16:
        formatted.push_back(display(va_arg(args, int16_t)));
        break;
      case Type::Int32:
        formatted.push_back(display(va_arg(args, int32_t)));
        break;
      case Type::Int64:
        formatted.push_back(display(va_arg(args, int64_t)));
        break;
      case Type::UInt8:
        formatted.push_back(display(va_arg(args, uint8_t)));
        break;
      case Type::UInt16:
        formatted.push_back(display(va_arg(args, uint16_t)));
        break;
      case Type::UInt32:
        formatted.push_back(display(va_arg(args, uint32_t)));
        break;
      case Type::UInt64:
        formatted.push_back(display(va_arg(args, uint32_t)));
        break;
      case Type::Float32:
        formatted.push_back(display(va_arg(args, float)));
        break;
      case Type::Float64:
        formatted.push_back(display(va_arg(args, double)));
        break;
      default:
        // MALO, ESO NO SE HACE
        break;
    }
  }

  return content.run(formatted);
}
*/

std::string Locale::display(bool arg) {
  // TODO: Implement method.
  (void)arg;

  return "false";
}

std::string Locale::display(int8_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0i8";
}

std::string Locale::display(int16_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0i16";
}

std::string Locale::display(int32_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0i32";
}

std::string Locale::display(int64_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0i64";
}

std::string Locale::display(uint8_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0u8";
}

std::string Locale::display(uint16_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0u16";
}

std::string Locale::display(uint32_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0u32";
}

std::string Locale::display(uint64_t arg) {
  // TODO: Implement method.
  (void)arg;

  return "0u64";
}

std::string Locale::display(float arg) {
  // TODO: Implement method.
  (void)arg;

  return "0.0f";
}

std::string Locale::display(double arg) {
  // TODO: Implement method.
  (void)arg;

  return "0.0d";
}

template <typename... T>
std::string Locale::format(const std::string& key, T... args) {
  const auto& content = keys_.at(key);

  std::vector<std::string> formatted{};
  nextArgument(formatted, args...);

  return content.run(formatted);
}
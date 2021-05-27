// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Information/Locale.h"

#include <cassert>

#include "Parser/FileParser.h"

void Locale::init(const std::string& locale) {
  locale_ = locale;

  std::filesystem::path root{"languages"};
  std::ifstream s{root / locale / ".meta.txt"};
  FileParser fp{s};
  const auto map = fp.run();
  name_ = map.at("NAME").run({});

  // TODO(Pablo): Assign all other properties here
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

void Locale::load() {
  std::filesystem::path root{"languages"};
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  root.append(locale());
  assert(std::filesystem::exists(root));
  assert(std::filesystem::is_directory(root));

  load(root, "");
}

#include "Information/Locale.h"

#include <gtest/gtest.h>

#include <fstream>

TEST(Locale, non_initialized_state) {
  Locale l{};
  EXPECT_TRUE(l.name().empty());
  EXPECT_TRUE(l.locale().empty());
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, initialized_state) {
  Locale l{};
  EXPECT_NO_THROW(l.init("en-US"));
  EXPECT_EQ(l.name(), "English (United States)");
  EXPECT_EQ(l.locale(), "en-US");
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, load_with_no_content) {
  Locale l{};
  EXPECT_NO_THROW(l.init("en-US"));
  EXPECT_NO_THROW(l.load());
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, load_with_content) {
  std::filesystem::path path{"languages"};
  path.append("fr-FR");

  std::filesystem::create_directory(path);

  const auto meta = path / ".meta.txt";
  std::ofstream fMeta(meta);
  fMeta << "NAME=\"Français (France)\"\n";
  fMeta.close();

  const auto misc = path / "misc.txt";
  std::ofstream fMisc(misc);
  fMisc << "HELLO=\"Hello {0}!\"\n";
  fMisc.close();

  Locale l{};
  EXPECT_NO_THROW(l.init("fr-FR"));
  EXPECT_NO_THROW(l.load());
  EXPECT_EQ(l.size(), 1);

  EXPECT_EQ(l.get("HELLO").run({"Drakhtar"}), "Hello Drakhtar!");

  std::filesystem::remove(misc);
  std::filesystem::remove(meta);
  std::filesystem::remove(path);
}

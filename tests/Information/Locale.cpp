#include "Information/Locale.h"

#include <gtest/gtest.h>

#include <fstream>

#include "LocaleManager.h"

TEST(Locale, non_initialized_state) {
  LocaleManager manager{};
  Locale l{manager};

  EXPECT_TRUE(l.name().empty());
  EXPECT_TRUE(l.locale().empty());
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, initialized_state) {
  LocaleManager manager{};
  Locale l{manager};

  EXPECT_NO_THROW(l.init("en-US"));
  EXPECT_EQ(l.name(), "English (United States)");
  EXPECT_EQ(l.locale(), "en-US");
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, load_with_no_content) {
  LocaleManager manager{};
  Locale l{manager};

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

  LocaleManager manager{};
  Locale l{manager};

  EXPECT_NO_THROW(l.init("fr-FR"));
  EXPECT_NO_THROW(l.load());
  EXPECT_EQ(l.size(), 1);

  EXPECT_EQ(l.get("HELLO").run({"Drakhtar"}), "Hello Drakhtar!");

  std::filesystem::remove(misc);
  std::filesystem::remove(meta);
  std::filesystem::remove(path);
}

TEST(Locale, load_asset) {
  std::filesystem::path path{"languages"};
  path.append("de-DE");

  std::filesystem::create_directory(path);

  const auto meta = path / ".meta.txt";
  std::ofstream fMeta(meta);
  fMeta << "NAME=\"Deutsche (Deutschland)\"\n";
  fMeta.close();

  const auto img = path / "img.jpg";
  std::ofstream fImg(img);
  fImg << "This is an image\"\n";
  fImg.close();

  const auto images = path / "images";
  std::filesystem::create_directory(images);

  const auto img2 = images / "img2.jpg";
  std::ofstream fImg2(img2);
  fImg2 << "This is an image\"\n";
  fImg2.close();

  LocaleManager manager{};
  Locale l{manager};

  EXPECT_NO_THROW(l.init("de-DE"));
  EXPECT_NO_THROW(l.load());
  EXPECT_EQ(l.assetsSize(), 2);
  EXPECT_EQ(l.getAsset("img.jpg"), "languages\\de-DE\\img.jpg");
  EXPECT_EQ(l.getAsset("images/img2.jpg"),
            "languages\\de-DE\\images\\img2.jpg");

  std::filesystem::remove(img2);
  std::filesystem::remove(images);
  std::filesystem::remove(img);
  std::filesystem::remove(meta);
  std::filesystem::remove(path);
}

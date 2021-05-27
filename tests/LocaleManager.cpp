#include "LocaleManager.h"

#include <gtest/gtest.h>

#include <fstream>

#include "Utils/Util.h"

TEST(LocaleManager, non_initialized_state) {
  LocaleManager m{};
  EXPECT_FALSE(m.initialized());
  EXPECT_TRUE(m.list().empty());
}

TEST(LocaleManager, initialized_state) {
  LocaleManager m{};
  EXPECT_NO_THROW(m.init());
  EXPECT_TRUE(m.initialized());
  EXPECT_EQ(m.list().size(), 4);

  EXPECT_TRUE(m.has("en"));
  EXPECT_TRUE(m.has("en-US"));
  EXPECT_TRUE(m.has("es"));
  EXPECT_TRUE(m.has("es-ES"));

  EXPECT_FALSE(m.loaded("en"));
  EXPECT_FALSE(m.loaded("en-US"));
  EXPECT_FALSE(m.loaded("es"));
  EXPECT_FALSE(m.loaded("es-ES"));
}

TEST(LocaleManager, load_locale) {
  LocaleManager m{};
  EXPECT_NO_THROW(m.init());

  EXPECT_TRUE(m.load("en-US"));

  EXPECT_TRUE(m.loaded("en"));
  EXPECT_TRUE(m.loaded("en-US"));
  EXPECT_FALSE(m.loaded("es"));
  EXPECT_FALSE(m.loaded("es-ES"));

  EXPECT_EQ(m.get("en-US").name(), "English (United States)");
  EXPECT_EQ(m.get("en-US").locale(), "en-US");
}

TEST(LocaleManager, load_file) {
  LocaleManager m{};

  std::filesystem::path path{"languages"};
  path.append("fr-FR");

  std::ofstream ofs(path);
  ofs << "NAME=\"Français (France)\"\n";
  ofs.close();

  EXPECT_NO_THROW(m.init());
  EXPECT_FALSE(m.has("fr-FR"));
  EXPECT_FALSE(m.load("fr-FR"));
  EXPECT_FALSE(m.loaded("fr-FR"));

  std::filesystem::remove(path);
}

TEST(LocaleManager, load_folder_without_meta) {
  LocaleManager m{};

  std::filesystem::path path{"languages"};
  path.append("hi-IN");

  std::filesystem::create_directory(path);

  EXPECT_NO_THROW(m.init());
  EXPECT_FALSE(m.has("hi-IN"));
  EXPECT_FALSE(m.load("hi-IN"));
  EXPECT_FALSE(m.loaded("hi-IN"));

  std::filesystem::remove(path);
}

TEST(LocaleManager, load_all) {
  LocaleManager m{};
  EXPECT_NO_THROW(m.init());

  EXPECT_TRUE(m.load());

  EXPECT_TRUE(m.loaded("en"));
  EXPECT_TRUE(m.loaded("en-US"));
  EXPECT_TRUE(m.loaded("es"));
  EXPECT_TRUE(m.loaded("es-ES"));

  EXPECT_EQ(m.get("en").name(), "English");
  EXPECT_EQ(m.get("en").locale(), "en");

  EXPECT_EQ(m.get("en-US").name(), "English (United States)");
  EXPECT_EQ(m.get("en-US").locale(), "en-US");

  EXPECT_EQ(m.get("es").name(), "Español");
  EXPECT_EQ(m.get("es").locale(), "es");

  EXPECT_EQ(m.get("es-ES").name(), "Español (España)");
  EXPECT_EQ(m.get("es-ES").locale(), "es-ES");
}

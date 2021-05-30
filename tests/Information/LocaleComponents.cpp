#include "Information/LocaleComponents.h"

#include <gtest/gtest.h>

#include <fstream>

TEST(LocaleComponents, constructor_language_only) {
  LocaleComponents l{"ja"};
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_TRUE(l.country.empty());
}

TEST(LocaleComponents, constructor_country_only) {
  LocaleComponents l{"ja-JP"};
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_EQ(l.country, "JP");
}

TEST(LocaleComponents, constructor_all) {
  LocaleComponents l{"ja-Kata-JP"};
  EXPECT_EQ(l.language, "ja");
  EXPECT_EQ(l.script, "Kata");
  EXPECT_EQ(l.country, "JP");
}

TEST(LocaleComponents, fallback_argument_language_only) {
  LocaleComponents l{"ja"};
  EXPECT_FALSE(l.fallback(l));
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_TRUE(l.country.empty());
}

TEST(LocaleComponents, fallback_argument_country_only) {
  LocaleComponents l{"ja-JP"};
  EXPECT_TRUE(l.fallback(l));
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_TRUE(l.country.empty());
}

TEST(LocaleComponents, fallback_argument_all) {
  LocaleComponents l{"ja-Kata-JP"};
  EXPECT_TRUE(l.fallback(l));
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_EQ(l.country, "JP");
}

TEST(LocaleComponents, fallback_language_only) {
  LocaleComponents l{"ja"};
  EXPECT_FALSE(l.fallback(l));
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_TRUE(l.country.empty());
}

TEST(LocaleComponents, fallback_country_only) {
  LocaleComponents l{"ja-JP"};
  EXPECT_TRUE(l.fallback());
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_TRUE(l.country.empty());
}

TEST(LocaleComponents, fallback_all) {
  LocaleComponents l{"ja-Kata-JP"};
  EXPECT_TRUE(l.fallback());
  EXPECT_EQ(l.language, "ja");
  EXPECT_TRUE(l.script.empty());
  EXPECT_EQ(l.country, "JP");
}

TEST(LocaleComponents, string_language_only) {
  LocaleComponents l{"ja"};
  EXPECT_EQ(l.string(), "ja");
}

TEST(LocaleComponents, string_country_only) {
  LocaleComponents l{"ja-JP"};
  EXPECT_EQ(l.string(), "ja-JP");
}

TEST(LocaleComponents, string_all) {
  LocaleComponents l{"ja-Kata-JP"};
  EXPECT_EQ(l.string(), "ja-Kata-JP");
}

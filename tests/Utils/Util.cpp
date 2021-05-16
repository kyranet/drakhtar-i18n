#include "Utils/Util.h"

#include <gtest/gtest.h>

TEST(UtilsUtil, isLetter) {
  EXPECT_TRUE(Util::isLetter('a'));
  EXPECT_TRUE(Util::isLetter('k'));
  EXPECT_TRUE(Util::isLetter('z'));
  EXPECT_TRUE(Util::isLetter('A'));
  EXPECT_TRUE(Util::isLetter('K'));
  EXPECT_TRUE(Util::isLetter('Z'));
  EXPECT_FALSE(Util::isLetter('.'));
  EXPECT_FALSE(Util::isLetter('_'));
  EXPECT_FALSE(Util::isLetter('$'));
}

TEST(UtilsUtil, isNotLetter) {
  EXPECT_FALSE(Util::isNotLetter('a'));
  EXPECT_FALSE(Util::isNotLetter('k'));
  EXPECT_FALSE(Util::isNotLetter('z'));
  EXPECT_FALSE(Util::isNotLetter('A'));
  EXPECT_FALSE(Util::isNotLetter('K'));
  EXPECT_FALSE(Util::isNotLetter('Z'));
  EXPECT_TRUE(Util::isNotLetter('.'));
  EXPECT_TRUE(Util::isNotLetter('_'));
  EXPECT_TRUE(Util::isNotLetter('$'));
}

TEST(UtilsUtil, parseLocale_empty) {
  const auto locale = Util::parseLocale("");
  EXPECT_EQ(locale.name, "");
  EXPECT_EQ(locale.language, "en");
  EXPECT_EQ(locale.country, "US");
}

TEST(UtilsUtil, parseLocale_en) {
  const auto locale = Util::parseLocale("en");
  EXPECT_EQ(locale.name, "en");
  EXPECT_EQ(locale.language, "en");
  EXPECT_EQ(locale.country, "");
}

TEST(UtilsUtil, parseLocale_en_US) {
  const auto locale = Util::parseLocale("en_US");
  EXPECT_EQ(locale.name, "en_US");
  EXPECT_EQ(locale.language, "en");
  EXPECT_EQ(locale.country, "US");
}

TEST(UtilsUtil, parseLocale_en_dash_US) {
  const auto locale = Util::parseLocale("en-US");
  EXPECT_EQ(locale.name, "en-US");
  EXPECT_EQ(locale.language, "en");
  EXPECT_EQ(locale.country, "US");
}

TEST(UtilsUtil, parseLocale_es_ES) {
  const auto locale = Util::parseLocale("es_ES");
  EXPECT_EQ(locale.name, "es_ES");
  EXPECT_EQ(locale.language, "es");
  EXPECT_EQ(locale.country, "ES");
}

TEST(UtilsUtil, parseLocale_es_dash_ES) {
  const auto locale = Util::parseLocale("es-ES");
  EXPECT_EQ(locale.name, "es-ES");
  EXPECT_EQ(locale.language, "es");
  EXPECT_EQ(locale.country, "ES");
}

TEST(UtilsUtil, parseLocale_es_dash_ES_UTF_dash_8) {
  const auto locale = Util::parseLocale("es-ES.UTF-8");
  EXPECT_EQ(locale.name, "es-ES.UTF-8");
  EXPECT_EQ(locale.language, "es");
  EXPECT_EQ(locale.country, "ES");
}

TEST(UtilsUtil, getLocale) {
  const auto locale = Util::getLocale();
  EXPECT_GT(locale.name.length(), 0);
  EXPECT_GT(locale.language.length(), 0);
  EXPECT_GT(locale.country.length(), 0);
}

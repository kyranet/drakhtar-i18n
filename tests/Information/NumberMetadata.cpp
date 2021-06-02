#include "Information/NumberMetadata.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "Parser/FileParser.h"

TEST(NumberMetadata, latn) {
  std::filesystem::path path{"languages"};
  std::ifstream s{path / ".numeric" / "latn.txt"};
  NumberMetadata meta{FileParser(s).run()};

  EXPECT_EQ(meta.decimal(), ",");
  EXPECT_EQ(meta.group(), ".");
  EXPECT_EQ(meta.list(), ";");
  EXPECT_EQ(meta.percent(), "%");
  EXPECT_EQ(meta.plus(), "+");
  EXPECT_EQ(meta.minus(), "-");
  EXPECT_EQ(meta.approximately(), "↑↑↑");
  EXPECT_EQ(meta.exponential(), "e");
  EXPECT_EQ(meta.superscriptingExponent(), "×");
  EXPECT_EQ(meta.perMille(), "‰");
  EXPECT_EQ(meta.infinity(), "∞");
  EXPECT_EQ(meta.nan(), "NaN");
  EXPECT_EQ(meta.timeSeparator(), ":");

  EXPECT_EQ(meta.at(0), "0");
  EXPECT_EQ(meta.at(1), "1");
  EXPECT_EQ(meta.at(2), "2");
  EXPECT_EQ(meta.at(3), "3");
  EXPECT_EQ(meta.at(4), "4");
  EXPECT_EQ(meta.at(5), "5");
  EXPECT_EQ(meta.at(6), "6");
  EXPECT_EQ(meta.at(7), "7");
  EXPECT_EQ(meta.at(8), "8");
  EXPECT_EQ(meta.at(9), "9");
}

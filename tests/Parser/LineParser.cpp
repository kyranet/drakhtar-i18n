#include "Parser/LineParser.h"

#include <gtest/gtest.h>

TEST(LineParser, run_simple_key) {
  std::istringstream in{"key=\"value\""};
  LineParser lp{in};

  const auto v = lp.run();
  EXPECT_EQ(v.first, "key");
  EXPECT_EQ(v.second.run({}), "value");
}

TEST(LineParser, run_complex_key) {
  std::istringstream in{"KeY_123_=\"value\""};
  LineParser lp{in};

  const auto v = lp.run();
  EXPECT_EQ(v.first, "KeY_123_");
  EXPECT_EQ(v.second.run({}), "value");
}

TEST(LineParser, run_invalid_key_special_characters) {
  std::istringstream in{"@key$=\"value\""};
  LineParser lp{in};

  EXPECT_THROW(lp.run(), std::runtime_error);
}

TEST(LineParser, run_invalid_key_space) {
  std::istringstream in{"key =\"value\""};
  LineParser lp{in};

  EXPECT_THROW(lp.run(), std::runtime_error);
}
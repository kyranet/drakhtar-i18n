#include "Parser/Strings/StringParser.h"

#include <gtest/gtest.h>

#include "Parser/Strings/StringContent.h"

TEST(StringParser, run_simple_string) {
  std::istringstream in{"Hello!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello!");
}

TEST(StringParser, run_string_with_variable) {
  std::istringstream in{"Hello {0}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello Drakhtar!");
}

TEST(StringParser, run_string_with_octal) {
  std::istringstream in{"Hello \\20!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello \20!");
}

TEST(StringParser, run_string_with_hexadecimal) {
  std::istringstream in{"Hello \\x60!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello \x60!");
}

TEST(StringParser, run_string_with_escaped_braces) {
  std::istringstream in{"Hello \\{0}\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello {0}");
}

TEST(StringParser, run_string_with_special_characters) {
  std::istringstream in{"Hello\\nWorld\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello\nWorld");
}

TEST(StringParser, run_string_with_early_end) {
  std::istringstream in{"Hello!\" How are you?"};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello!");
}

TEST(StringParser, run_string_with_escaped_new_line) {
  std::istringstream in{"Hello!\\\n How are you?\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello! How are you?");
}

#include "Parser/Strings/StringParser.h"

#include <gtest/gtest.h>

#include "Parser/Strings/StringContent.h"

TEST(StringParser, run_simple_string) {
  std::istringstream in{"Hello!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello!");
  EXPECT_EQ(in.tellg(), 7);
}

TEST(StringParser, run_string_with_variable) {
  std::istringstream in{"Hello {0}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello Drakhtar!");
  EXPECT_EQ(in.tellg(), 11);
}

TEST(StringParser, run_string_with_octal) {
  std::istringstream in{"Hello \\20!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello \20!");
  EXPECT_EQ(in.tellg(), 11);
}

TEST(StringParser, run_string_with_invalid_octal) {
  std::istringstream in{"Hello \\9!\""};
  StringParser sp{in};

  EXPECT_THROW((void)sp.run(), std::runtime_error);
}

TEST(StringParser, run_string_with_hexadecimal) {
  std::istringstream in{"Hello \\x60!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello \x60!");
  EXPECT_EQ(in.tellg(), 12);
}

TEST(StringParser, run_string_with_invalid_hexadecimal_invalid_range) {
  std::istringstream in{"Hello \\xZ3!\""};
  StringParser sp{in};

  EXPECT_THROW((void)sp.run(), std::runtime_error);
}

TEST(StringParser, run_string_with_invalid_hexadecimal_too_short) {
  std::istringstream in{"Hello \\x3\""};
  StringParser sp{in};

  EXPECT_THROW((void)sp.run(), std::runtime_error);
}

TEST(StringParser, run_string_with_escaped_braces) {
  std::istringstream in{"Hello \\{0}\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello {0}");
  EXPECT_EQ(in.tellg(), 11);
}

TEST(StringParser, run_string_with_special_characters) {
  std::istringstream in{"Hello\\nWorld\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello\nWorld");
  EXPECT_EQ(in.tellg(), 13);
}

TEST(StringParser, run_string_with_early_end) {
  std::istringstream in{"Hello!\" How are you?"};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello!");
  EXPECT_EQ(in.tellg(), 7);
}

TEST(StringParser, run_string_with_escaped_new_line) {
  std::istringstream in{"Hello!\\\n How are you?\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.run({}), "Hello! How are you?");
  EXPECT_EQ(in.tellg(), 22);
}

TEST(StringParser, run_string_with_string_variable) {
  std::istringstream in{"Hello {0s}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello Drakhtar!");
  EXPECT_EQ(in.tellg(), 12);
}
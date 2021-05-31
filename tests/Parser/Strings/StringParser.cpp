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

  auto variableTypes = v.types();

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello Drakhtar!");
  EXPECT_EQ(in.tellg(), 12);

  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::String);
}

TEST(StringParser, run_string_with_boolean_variable) {
  std::istringstream in{"Hello {0b}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Boolean);
}

TEST(StringParser, run_string_with_8_bytes_integer_variable) {
  std::istringstream in{"Hello {0i8}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Int8);
}

TEST(StringParser, run_string_with_16_bytes_integer_variable) {
  std::istringstream in{"Hello {0i16}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Int16);
}

TEST(StringParser, run_string_with_32_bytes_integer_variable) {
  std::istringstream in{"Hello {0i32}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Int32);
}

TEST(StringParser, run_string_with_64_bytes_integer_variable) {
  std::istringstream in{"Hello {0i64}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Int64);
}

TEST(StringParser, run_string_with_8_bytes_unsigned_variable) {
  std::istringstream in{"Hello {0u8}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::UInt8);
}

TEST(StringParser, run_string_with_16_bytes_unsigned_variable) {
  std::istringstream in{"Hello {0u16}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::UInt16);
}

TEST(StringParser, run_string_with_32_bytes_unsigned_variable) {
  std::istringstream in{"Hello {0u32}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::UInt32);
}

TEST(StringParser, run_string_with_64_bytes_unsigned_variable) {
  std::istringstream in{"Hello {0u64}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::UInt64);
}

TEST(StringParser, run_string_with_32_bytes_float_variable) {
  std::istringstream in{"Hello {0f32}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Float32);
}

TEST(StringParser, run_string_with_64_bytes_float_variable) {
  std::istringstream in{"Hello {0f64}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  auto variableTypes = v.types();
  EXPECT_EQ(variableTypes.size(), 1);
  EXPECT_EQ(variableTypes[0], Type::Float64);
}

TEST(StringParser, run_string_with_truncated_variable) {
  std::istringstream in{"Hello {"};
  StringParser sp{in};

  EXPECT_THROW((void)sp.run(), std::runtime_error);
}
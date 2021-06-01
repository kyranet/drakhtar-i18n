#include "Parser/Strings/StringContent.h"

#include <gtest/gtest.h>

TEST(StringContent, dynamic_when_given_empty_then_returns_false) {
  StringContent content{};
  EXPECT_FALSE(content.dynamic());
}

TEST(StringContent, dynamic_when_given_content_only_then_returns_false) {
  StringContent content{};

  content.add("Hello");
  EXPECT_FALSE(content.dynamic());
}

TEST(StringContent, dynamic_when_given_a_variable_then_returns_true) {
  StringContent content{};

  content.add(VariableInfo{0, Type::String, {}});
  EXPECT_TRUE(content.dynamic());
}

TEST(StringContent, size_when_given_empty_then_returns_zero) {
  StringContent content{};
  EXPECT_EQ(content.size(), 0);
}

TEST(StringContent, size_when_given_content_only_then_returns_one) {
  StringContent content{};

  content.add("Hello");
  EXPECT_EQ(content.size(), 1);
}

TEST(StringContent, size_when_given_two_contents_then_returns_one) {
  StringContent content{};

  content.add("Hello");
  content.add("World");
  EXPECT_EQ(content.size(), 1);
}

TEST(StringContent, size_when_given_a_variable_then_returns_one) {
  StringContent content{};

  content.add(VariableInfo{0, Type::String, {}});
  EXPECT_EQ(content.size(), 1);
}

TEST(StringContent, size_when_given_a_content_and_a_variable_then_returns_two) {
  StringContent content{};

  content.add("Hello ");
  content.add(VariableInfo{0, Type::String, {}});
  EXPECT_EQ(content.size(), 2);
}

TEST(StringContent, size_when_given_three_parts_then_returns_three) {
  StringContent content{};

  content.add("Hello ");
  content.add(VariableInfo{0, Type::String, {}});
  content.add("!");
  EXPECT_EQ(content.size(), 3);
}

TEST(StringContent, run_when_empty_then_returns_empty_string) {
  StringContent content{};

  EXPECT_EQ(content.run({}), "");
}

TEST(StringContent, run_when_given_content_only_then_returns_content) {
  StringContent content{};

  content.add("Hello!");
  EXPECT_EQ(content.run({}), "Hello!");
}

TEST(StringContent, run_when_given_variable_only_then_returns_variable) {
  StringContent content{};

  content.add(VariableInfo{0, Type::String, {}});
  EXPECT_EQ(content.run({"Drakhtar"}), "Drakhtar");
}

TEST(StringContent, run_when_given_three_parts_then_returns_formatted_string) {
  StringContent content{};

  content.add("Hello ");
  content.add(VariableInfo{0, Type::String, {}});
  content.add("!");
  EXPECT_EQ(content.run({"Drakhtar"}), "Hello Drakhtar!");
}

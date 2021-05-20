#include "Parser/FileParser.h"

#include <gtest/gtest.h>

TEST(FileParser, run_simple_file) {
  std::istringstream in{"key1=\"value1\"\nkey2=\"value2\"\nkey3=\"value2\""};
  FileParser fp{in};

  const auto v = fp.run();
  EXPECT_EQ(v.size(), 3);
}

TEST(FileParser, run_commented_file) {
  std::istringstream in{
      "key1=\"value1\"\n# key2=\"value1\"\nkey3=\"value2\" # This is another "
      "comment"};
  FileParser fp{in};

  const auto v = fp.run();
  EXPECT_EQ(v.size(), 2);
}

TEST(FileParser, run__file_with_variables) {
  std::istringstream in{
      "key1=\"value1\"\nkey2=\"{0}\"\nkey3=\"value2\" # This is another "
      "comment"};
  FileParser fp{in};

  const auto v = fp.run();
  EXPECT_EQ(v.size(), 3);
}
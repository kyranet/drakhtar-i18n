#include "Parser/FileParser.h"

#include <gtest/gtest.h>

TEST(FileParser, run_simple_file) {
  std::istringstream in{"key1=\"value1\"\nkey2=\"value2\"\nkey3=\"value3\""};
  FileParser fp{in};

  auto v = fp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v["key1"].run({}), "value1");
  EXPECT_EQ(v["key2"].run({}), "value2");
  EXPECT_EQ(v["key3"].run({}), "value3");
}

TEST(FileParser, run_commented_file) {
  std::istringstream in{
      "key1=\"value1\"\n# key2=\"value2\"\nkey3=\"value3\" # This is another "
      "comment"};
  FileParser fp{in};

  auto v = fp.run();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v["key1"].run({}), "value1");
  EXPECT_EQ(v["key3"].run({}), "value3");
}

TEST(FileParser, run__file_with_variables) {
  std::istringstream in{
      "key1=\"value1\"\nkey2=\"{0}\"\nkey3=\"value3\" # This is another "
      "comment"};
  FileParser fp{in};

  auto v = fp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v["key1"].run({}), "value1");
  EXPECT_EQ(v["key3"].run({}), "value3");
}
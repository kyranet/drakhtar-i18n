#include "Parser/CommentParser.h"

#include <gtest/gtest.h>

TEST(CommentParser, run) {
  std::istringstream in{"hello world"};
  CommentParser lp{in};

  EXPECT_NO_THROW(lp.run());
  EXPECT_EQ(in.tellg(), -1);
}

TEST(CommentParser, run_with_newline) {
  std::istringstream in{"hello world\nkey=\"foo\""};
  CommentParser lp{in};

  EXPECT_NO_THROW(lp.run());
  EXPECT_EQ(in.tellg(), 12);
}

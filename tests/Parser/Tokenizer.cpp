#include "Parser/Tokenizer.h"

#include <gtest/gtest.h>

TEST(Tokenizer, next) {
  std::istringstream in{"hi"};
  Tokenizer t{in};

  EXPECT_FALSE(t.finished());
  EXPECT_EQ(t.next(), 'h');

  EXPECT_FALSE(t.finished());
  EXPECT_EQ(t.next(), 'i');

  // Test stream's behaviour where the eof bit isn't set until it reads an
  // out-of-bounds value:
  EXPECT_FALSE(t.finished());
  EXPECT_NO_THROW(t.next());
  EXPECT_TRUE(t.finished());
}

TEST(Tokenizer, next_with_char) {
  std::istringstream in{"hi"};
  Tokenizer t{in};

  char c;
  EXPECT_TRUE(t.next(c));
  EXPECT_EQ(c, 'h');

  EXPECT_TRUE(t.next(c));
  EXPECT_EQ(c, 'i');

  EXPECT_FALSE(t.next(c));
}

TEST(Tokenizer, undo) {
  std::istringstream in{"hi"};
  Tokenizer t{in};

  char c;
  EXPECT_TRUE(t.next(c));
  EXPECT_EQ(c, 'h');

  t.undo();

  EXPECT_TRUE(t.next(c));
  EXPECT_EQ(c, 'h');

  EXPECT_TRUE(t.next(c));
  EXPECT_EQ(c, 'i');
}

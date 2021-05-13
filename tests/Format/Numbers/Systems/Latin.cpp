#include "Format/Numbers/Systems/Latin.h"

#include <gtest/gtest.h>

TEST(FormatNumbersSystemsLatin, get) {
  Latin system{};

  EXPECT_EQ(system.get(0), '0');
  EXPECT_EQ(system.get(1), '1');
  EXPECT_EQ(system.get(2), '2');
  EXPECT_EQ(system.get(3), '3');
  EXPECT_EQ(system.get(4), '4');
  EXPECT_EQ(system.get(5), '5');
  EXPECT_EQ(system.get(6), '6');
  EXPECT_EQ(system.get(7), '7');
  EXPECT_EQ(system.get(8), '8');
  EXPECT_EQ(system.get(9), '9');
}

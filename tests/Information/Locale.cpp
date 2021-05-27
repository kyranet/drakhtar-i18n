#include "Information/Locale.h"

#include <gtest/gtest.h>

TEST(Locale, non_initialized_state) {
  Locale l{};
  EXPECT_TRUE(l.name().empty());
  EXPECT_TRUE(l.locale().empty());
  EXPECT_EQ(l.size(), 0);
}

TEST(Locale, initialized_state) {
  Locale l{};
  EXPECT_NO_THROW(l.init("en-US"));
  EXPECT_EQ(l.name(), "English (United States)");
  EXPECT_EQ(l.locale(), "en-US");
  EXPECT_EQ(l.size(), 0);
}

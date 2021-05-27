#include "Format/Strings/TransformerManager.h"

#include <gtest/gtest.h>

#include "Parser/Strings/StringContent.h"
#include "Parser/Strings/StringParser.h"

TEST(TransformerManager, run_wrong_transformer) {
  std::istringstream in{"Hello {0:wrong}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_THROW((void)v.run({"Drakhtar"}), std::runtime_error);
}

TEST(TransformerManager, run_multiple_transformer) {
  std::istringstream in{"Hello {0:uppercase:lowercase}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello drakhtar!");
}
#include "Format/Strings/UppercaseTransformer.h"

#include <gtest/gtest.h>

#include "Parser/Strings/StringContent.h"
#include "Parser/Strings/StringParser.h"

TEST(UppercaseTransformer, run_variable_uppercase) {
  std::istringstream in{"Hello {0:uppercase}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"Drakhtar"}), "Hello DRAKHTAR!");
  EXPECT_EQ(in.tellg(), 11);
}

#include "Format/Strings/LowercaseTransformer.h"

#include <gtest/gtest.h>

#include "Parser/Strings/StringContent.h"
#include "Parser/Strings/StringParser.h"

TEST(LowercaseTransformer, run_variable_lowercase) {
  std::istringstream in{"Hello {0:lowercase}!\""};
  StringParser sp{in};

  const auto v = sp.run();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.run({"DRAKHTAR"}), "Hello drakhtar!");
}

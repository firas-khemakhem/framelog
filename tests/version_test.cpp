#include <framelog/version.hpp>

#include <gtest/gtest.h>

#include <regex>
#include <string>

TEST(Version, MatchesBuildVersion) {
  EXPECT_STREQ(flog::version(), FRAMELOG_EXPECTED_VERSION);
}

TEST(Version, IsSemanticVersion) {
  const std::string value{flog::version()};
  EXPECT_FALSE(value.empty());
  EXPECT_TRUE(std::regex_match(value, std::regex{R"(^\d+\.\d+\.\d+$)"}));
}

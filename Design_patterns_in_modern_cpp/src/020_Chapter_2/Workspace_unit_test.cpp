// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <sstream>
#include <iostream>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(BuilderPatternIntro, Example) {
    std::string words[] = { "hello", "world" };
    std::ostringstream oss;
    oss << "<ul>\n";
    for (auto w : words)
      oss << " <li>" << w << "</li>\n";
    oss << "</ul>\n";
    std::cout << oss.str();
  }
} // namespace

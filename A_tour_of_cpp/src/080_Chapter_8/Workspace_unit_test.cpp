// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <utility>
#include <type_traits>

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(StringFunctions, Positive) {
    EXPECT_THAT(section_9_2::compose("nawin", "something.com"), Eq("nawin@something.com"));

    std::string str{ "Hello" };
    section_9_2::appendNewLine(str);
    EXPECT_THAT(str, Eq("Hello\n"));
    EXPECT_TRUE((std::is_same<decltype(str.c_str()), const char*>::value));
  }

  TEST(StringView, Positive) {
    std::string name{ "Nawin" };    
    auto s1 = section_9_3::cat(name, " is the best");
    EXPECT_THAT(s1, Eq("Nawin is the best"));

  }

  }  // namespace

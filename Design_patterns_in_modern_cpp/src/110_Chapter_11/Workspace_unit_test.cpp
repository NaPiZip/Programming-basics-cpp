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
using ::testing::Eq;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(AddingAndPrintingUsers, Positive) {
    User one{ "Nawin", "Piffel" };

    std::stringstream ss;
    ss << one;
    EXPECT_THAT(one.get_first_name(), Eq("Nawin"));
    EXPECT_THAT(one.get_last_name(), Eq("Piffel"));
    EXPECT_THAT(ss.str(), Eq("first name: Nawin last name: Piffel"));

    User two{ "Shit", "Piffel" };
    ss.str("");
    ss.clear();
    ss << two;
    EXPECT_THAT(two.get_first_name(), Eq("Shit"));
    EXPECT_THAT(two.get_last_name(), Eq("Piffel"));
    EXPECT_THAT(ss.str(), Eq("first name: Shit last name: Piffel"));
  }

  TEST(BoostImplementation, Positive) {
    User2 john{ "John", "Doe" };
    User2 jane{ "Jane", "Doe" };
    EXPECT_THAT(&john.last_name_.get(), Eq(&jane.last_name_.get()));
  }

  TEST(FormattedTextToUpper, Positive) {
    FormattedText text{ "some shit is here" };
    text.capitalize(5, 9);
    std::stringstream ss;
    ss << text;
    EXPECT_THAT(ss.str(), Eq("some SHIT is here"));
  }

  TEST(BetterFormattedTextToUpper, Positive) {
    BetterFormattedText bft{ "This is a brave new world" };
    bft.get_range(10, 15).capitalize = true;

    std::stringstream ss;
    ss << bft;
    EXPECT_THAT(ss.str(), Eq("This is a BRAVE new world"));
  }

} // namespace

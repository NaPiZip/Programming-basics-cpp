// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::StartsWith;
using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2+3, 5);
  }

  TEST(JournalConstructor, Positive) {
    Journal obj("asdas"s);

    EXPECT_THAT(obj.GetTitle(), StartsWith("asd"));    
  }

  TEST(JournalAdd, Positive) {
    Journal obj("asdas"s);

    obj.AddLine("Something");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));

    obj.AddLine("Something else");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));
  }

}  // namespace

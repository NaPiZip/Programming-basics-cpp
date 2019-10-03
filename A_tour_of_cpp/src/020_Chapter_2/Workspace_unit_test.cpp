// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::StartsWith;
using ::testing::HasSubstr;

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

  TEST(JournalSize, Positive) {
    Journal obj("asdas"s);

    obj.AddLine("Something");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));

    obj.AddLine("Something else");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));

    EXPECT_THAT(obj.size(), 2);
  }


  TEST(JournalIterators, Positive) {
    std::vector<std::string> string_list = { "Something", "Something else" };

    Journal obj("asdas"s);

    obj.AddLine(string_list[0]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));
    obj.AddLine(string_list[1]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));

    for (auto it(obj.begin()); it != obj.end(); ++it)
    {
      EXPECT_THAT(*it, HasSubstr(string_list[std::distance(obj.begin(), it)]));
    }
  }

}  // namespace

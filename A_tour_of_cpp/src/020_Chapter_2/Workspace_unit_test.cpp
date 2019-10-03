// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"


namespace {

  using ::testing::Ne;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(StructVectorInitTest, Positive) {
    EXPECT_THAT(section_2_2::ReadAndSum(2), Ne(0));
  }

  TEST(ClassVectorInitTest, Positive) {
    section_2_3::Vector v{ 4 };
    EXPECT_THAT(v.size(), 4);
    EXPECT_THAT(v[0], Ne(0));
  }

  TEST(UnionsAndVriants, Positive) {
    section_2_4::Entry a;

    // Configuring our type
    a.name = "Number"s;
    a.t = section_2_4::Type::num;
    a.v.i = 5;

    section_2_4::EntryVariant b;
    b.name = "Number"s;
    b.v = 5;

    EXPECT_THAT(std::holds_alternative<int>(b.v), true);
    EXPECT_THAT(std::get<int>(b.v), 5);
  }

  TEST(YestANotherVariant, Positive) {
    std::variant<int, float> v{ 3 };

    if (std::holds_alternative<int>(v)) {
      std::cout << "Variant is int: " << std::get<int>(v) << "\n";
    } else if (std::holds_alternative<float>(v)) {
      std::cout << "Variant is float: " << std::get<float>(v) << "\n";
    } else {
      std::cout << "Opps something went wrong!\n";
    }
  }

}  // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <utility>
#include <vector>
#include <map>

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(AccumulatorFunc, Positive) {
    std::vector vec{ 1, 2, 3, 4 };
    EXPECT_THAT(section_7_3::accumulate(vec.begin(), vec.end(), 10), Eq(20));
    EXPECT_THAT(section_7_3::accumulate(vec.begin(), vec.begin()+2, 10), Eq(13));
  }

  TEST(VariadicPrint, Positive) {
    section_7_3::print("asd"s, 1, '3', 3, 4.0f);
    section_7_3::print2("asd"s, 1, '3', 3, 4.0f);
  }

  TEST(FoldExpressions, Positive) {
    EXPECT_THAT(section_7_4::sum(1, 2, 35.5f), Eq(38));
    section_7_4::print("Hello!"s, ' ', "World ", 2017);
  }

  }  // namespace

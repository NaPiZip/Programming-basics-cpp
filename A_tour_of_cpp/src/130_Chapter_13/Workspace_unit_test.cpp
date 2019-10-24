// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>
#include <bitset>



namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(Simple, Positive) {
    std::unique_ptr<int> ptr = section_13_2::make_x(3);
    EXPECT_THAT(*ptr, Eq(3));
 }

  TEST(Bitsets, Positive) {
    std::bitset<5> bs1{"10010"};
    std::bitset<5> not_bs1= ~bs1;

    EXPECT_THAT(bs1, Eq(~not_bs1));
    std::cout << (bs1>>2);
  }

  }  // namespace

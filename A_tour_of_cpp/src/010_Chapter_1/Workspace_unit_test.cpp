// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>

using ::testing::StartsWith;
using ::testing::HasSubstr;

using std::string_literals::operator""s;

namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2+3, 5);
  }

  TEST(ArithmeticTest, ShouldPass) {
    int x = -1,
        y = 1;
    y = +x;
    std::cout << "Value for +x: "s << y << "\n";
  }

}  // namespace

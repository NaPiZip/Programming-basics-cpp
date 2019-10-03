// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>

using std::string_literals::operator""s;

namespace {
  constexpr int sum(int a, int b) { return a + b; }

  TEST(ConstexprTest, ShouldPass) {
    std::cout << "constexpr sum: "s << sum(1, 10) << "\n";
    EXPECT_THAT(sum(1, 10), 11);
  }

 
}  // namespace

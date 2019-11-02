// Copyright 2019, Nawin
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include "vec3.h"

using std::string_literals::operator""s;

namespace {
  constexpr int sum(int a, int b) { return a + b; }

  TEST(ConstexprTest, ShouldPass) {
    std::cout << "constexpr sum: "s << sum(1, 10) << "\n";
    EXPECT_THAT(sum(1, 10), 11);
   vec3 v{ 1,2,3 };
  }

 
}  // namespace

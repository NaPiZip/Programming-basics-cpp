// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>
#include <unordered_map>

namespace {

  using ::testing::Ne;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(ComplexBasicTest, Positive) {
    my_code::Complex a{ 1, 2 },
                     b{ 1, 4 };

    EXPECT_THAT(a.real(), 1);
    EXPECT_THAT(a.imag(), 2);

    EXPECT_TRUE(my_code::sqrt(a) == b);
    my_code::main();
  }

  TEST(StructuredBindingExample, Positive) {
    std::unordered_map<std::string, float> hash_map;
    hash_map.emplace("Nawin", 12.3f);
    hash_map.emplace("Belen", 23.4f);

    for (auto [name, money] : hash_map) {
      std::cout << name << ' ' << money << "$\n";
    }
  }

}  // namespace

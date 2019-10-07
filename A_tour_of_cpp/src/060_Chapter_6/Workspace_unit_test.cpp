// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>
#include <utility>

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(ExplicitConversion, Positive) {
    section_5_2::Vector a(3), c;
    
    //section_5_2::Vector b = 3; // Does not work due to explicit
  }

  TEST(DeepCopyConstructor, Positive) {
    section_5_2::Vector a{1,2,3};
    section_5_2::Vector b(a);
    b[0] = 2;

    EXPECT_THAT(a[0], Ne(b[0]));
    EXPECT_THAT(b.size(), Eq(3));
  }

  TEST(MoveConstructor, Positive) {
    section_5_2::Vector a{ 1,2,3,4 };

    EXPECT_THAT(a.size(), Eq(4));

    section_5_2::Vector b = std::move(a);
    EXPECT_THAT(a.size(), Eq(0));

    section_5_2::Vector c = section_5_2::returnVector();

  }

  }  // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>

namespace {

  using ::testing::Ne;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  }  // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <utility>

#include <concepts>

// This concept tests whether 'T::type' is a valid type
template<typename T>
concept has_type_member = requires { typename T::type; };


namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }


  }  // namespace

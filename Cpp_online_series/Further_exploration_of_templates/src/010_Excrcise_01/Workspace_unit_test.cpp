// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <array>
#include <iostream>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;
using ::testing::Eq;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(Typtraits, Derived)
  {
    struct A {};
    struct B : A {};
  
    EXPECT_TRUE( (check_if_is_derived_type<A, B>()));
  }

  TEST(StaticAssertion, Basic)
  {
    std::cout << (3, 'F') << (3+'F');
  }

  TEST(VariadicPrint, Simple)
  {
    print(1, 2, 3, "123", 'c');
  }
 } // namespace

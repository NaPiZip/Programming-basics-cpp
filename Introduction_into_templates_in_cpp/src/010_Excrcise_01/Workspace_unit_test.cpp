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

  TEST(SwapTemplateFunction, Positive)
  {
    int a = 4, b = 6;

    swap(a, b);
    EXPECT_THAT(a, Eq(6));
    EXPECT_THAT(b, Eq(4));
  }

  TEST(ArraySumFunction, Simple)
  {
    std::array<int,4> int_array{ 1,2,3,4 };
    std::array<float, 4> float_array{ 1.0,2.0,3.0,4.0 };

    EXPECT_THAT(sum(float_array), Eq(10));
    EXPECT_THAT(sum(int_array), Eq(10.0));
    std::cout << "Okay this works" << std::endl;
  }
  TEST(StackImplementation, Simple)
  {
    Stack<int> stack(2);
    stack.push(10);
    stack.push(20);

    try
    {
      stack.push(10);
      assert(false);
    }
    catch (StackException & e)
    {
      EXPECT_THAT(e.what(), ::testing::StrEq("Full Stack"));
    }

    EXPECT_THAT(stack.top(), Eq(20));
    stack.pop();
    EXPECT_THAT(stack.top(), Eq(10));
    stack.pop();

    try 
    {
      stack.pop();
      assert(false);
    } catch (StackException &e)
    {
      EXPECT_THAT(e.what(), ::testing::StrEq("Empty stack"));
    }
  }
 } // namespace

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

  TEST(StackImplementation, Advanced)
  {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    try
    {
      stack.push(30);
      
    }
    catch (StackException & e)
    {
      assert(false);
    }

    EXPECT_THAT(stack.top(), Eq(30));
    stack.pop();
    EXPECT_THAT(stack.top(), Eq(20));
    stack.pop();

    try 
    {
      stack.pop();
      stack.pop();
      assert(false);
    } catch (StackException &e)
    {
      EXPECT_THAT(e.what(), ::testing::StrEq("Empty stack"));
    }
  }
 } // namespace

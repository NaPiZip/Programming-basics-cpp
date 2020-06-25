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
  TEST(TupleImplementation, Basic) {
    tuple a{ 1,5.6 }, b{ 1,5.6 }, c{ 1,3.4 };
    tuple diffrent{ 1,1 };
    
    EXPECT_THAT(a.first(), Eq(1));
    EXPECT_THAT(a.second(), Eq(5.6));
    
    auto compare_a_b = a == b;
    auto compare_a_c = a == c;
    
    EXPECT_TRUE(compare_a_b);
    EXPECT_FALSE(compare_a_c);

    //auto comp = diffrent == a;
  }

  TEST(MyArray, Simple)
  {
    MyArray<int,double> arr;

    arr.add(tuple{ 4,5.6 });
    EXPECT_THAT(arr.get(4), Eq(5.6));

    try {
      arr.get(15);
    }
    catch (MyArrayException & e)
    {
      EXPECT_THAT(e.what(), ::testing::StrEq("Key not found"));
    }

    EXPECT_THAT(arr.getOrElse(4,1.0), Eq(5.6));
    EXPECT_THAT(arr.getOrElse(5,1.0), Eq(1.0));

    EXPECT_THAT(arr[4], Eq(5.6));
  }
  TEST(PolicyLogger, Basic) {
    Logger<StdOut> logger;
    Logger<NoOut> logger_2;

    logger.doSomething("asd");
    logger_2.doSomething("asd");
  }

 } // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <sstream>
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

  TEST(BasicMemento, Positive) {
    BankAccount ba{ 100 };
    auto m1 = ba.deposit(50);
    auto m2 = ba.deposit(25);
    
    std::stringstream ss;
    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 175\n")); 

    ss.clear();
    ss.str("");

    // undo m1
    ba.resore(m1);
    
    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 150\n")); 

    ss.clear();
    ss.str("");

    // undo m2
    ba.resore(m2);

    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 175\n")); 
  }

  TEST(MementoWithHistory, Positive) {
    BankAccount2 ba{ 100 };
    ba.deposit(50);
    ba.deposit(25);

    std::stringstream ss;
    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 175\n"));

    ss.clear();
    ss.str("");

    ba.undo();

    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 150\n"));

    ss.clear();
    ss.str("");

    ba.undo();

    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 100\n"));

    ss.clear();
    ss.str("");

    ba.redo();

    ss << ba;
    EXPECT_THAT(ss.str(), Eq("The balance is: 150\n"));

  }
 } // namespace

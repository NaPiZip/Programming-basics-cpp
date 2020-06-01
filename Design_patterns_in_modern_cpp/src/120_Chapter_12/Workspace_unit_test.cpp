// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>
#include <iostream>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(SmartPointers, Positive) {
    BankAccount* ba = new BankAccount;
    ba->deposit(299);
    auto ba2 = std::make_shared<BankAccount>();
    ba2->deposit(299);
  }

  TEST(LazyInstance, Positive) {
    Bitmap bmp{ "shitfile.png" };
    LazyBitmap lbmp{ "sameshit.png" };

    bmp.draw();
    lbmp.draw();
  }
  TEST(PingPong, Positive) {
    Pong p;

    tryit(p);
  }
} // namespace

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

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(ABasicObserver, Positive) {
    Person p{ 20 };
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(22);
    p.set_age(32);
  }
  TEST(ObserverWitSignals, Positive) {
    PersonWithSignal p{ 123 };
    auto conn = p.property_changed_.connect([](PersonWithSignal&, const std::string& prop_name) {
      std::cout << prop_name << " has been changed" << std::endl;
    });
    p.set_age(20);
    conn.disconnect();
  }
 } // namespace

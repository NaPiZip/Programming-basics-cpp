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

  TEST(Prototype, Simple) {
    Contact worker{
      "asd", new Address{ "asd", "aasd", 5 }
    };

    Contact john{ worker };
    john.name_ = "Bob";
  }

  TEST(PrototypeFactory, Simple) {
    auto john = EmployeeFactory::NewAuxOfficeEmployee("Bob", 123);
    auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane", 125);
  }

} // namespace

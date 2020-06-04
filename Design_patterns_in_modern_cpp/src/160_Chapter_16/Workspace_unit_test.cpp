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

  TEST(BasicIteratro, Positive) {
    BinaryTree<std::string> family{
      new Node<std::string>{ "me",
          new Node<std::string>{ "mother",
              new Node<std::string>{ "mother's mother" },
              new Node<std::string>{ "mother's father" } },
          new Node<std::string>{ "father" } }
    };
    for (auto it = family.begin(); it != family.end(); ++it)
      std::cout << (*it).value_ << "\n";
  }

 } // namespace

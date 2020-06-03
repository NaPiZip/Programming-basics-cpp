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
  TEST(ParserAndLexerTest, Positive) {
    std::string input{ "(13-4)-(12+1)" };
    auto tokens = lex(input);
    auto parsed = parse(tokens);

    EXPECT_THAT(parsed->eval(), Eq(-4));
  }

 } // namespace

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
  TEST(SimpleChainOfCommands, Positive) {
    Creature goblin{ "Nawin", 1, 1 };
    CreatureModifier root{ goblin };
    DoubleAttackModifier r1{ goblin };
    DoubleAttackModifier r1_2{ goblin };
    IncreaseDefenseModifier r2{ goblin };

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();
    std::stringstream ss;
    ss << goblin;
    EXPECT_THAT(ss.str(), Eq("Nawin a: 4 d: 1\n"));
  }

  TEST(MessageBroker, Positive) {
    Game game;
    Creature2 goblin{ game, "Strong Idiot", 2, 2 };
    std::stringstream ss;
    ss << goblin;
    EXPECT_THAT(ss.str(), Eq("Strong Idiot a: 2 d: 2\n"));
    ss.str("");
    ss.clear();
    {
      DoubleAttackModifier2 dam{ game, goblin };
      ss << goblin;
      EXPECT_THAT(ss.str(), Eq("Strong Idiot a: 4 d: 2\n"));
      ss.str("");
      ss.clear();
    }
    ss << goblin;
    EXPECT_THAT(ss.str(), Eq("Strong Idiot a: 2 d: 2\n"));
  }

} // namespace

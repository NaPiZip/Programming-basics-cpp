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
  TEST(SimpleCommand, Positive) {
    BankAccount ba;
    BankAccountCommand cmd{ ba, BankAccountCommand::deposit, 100 };
    EXPECT_THAT(ba.balance_, Eq(0));

    cmd.call();

    EXPECT_THAT(ba.balance_, Eq(100));
  }
  TEST(CQS, Positive) {
    Creature tim{ 1, 5 };
    CreatureCommand increase{ CreatureCommand::increaseBy, CreatureAbility::strenght, 10 };
    CreatureCommand decrease{ CreatureCommand::decreaseBy, CreatureAbility::agility, 5 };
    CreatureQuery get_strength{ CreatureAbility::strenght };
    CreatureQuery get_agility{ CreatureAbility::agility };
    
    tim.process_query(get_strength);
    tim.process_query(get_agility);
    EXPECT_THAT(get_strength.value_, Eq(1));
    EXPECT_THAT(get_agility.value_, Eq(5));

    tim.process_command(increase);
    tim.process_command(decrease);

    tim.process_query(get_strength);
    tim.process_query(get_agility);
    EXPECT_THAT(get_strength.value_, Eq(11));
    EXPECT_THAT(get_agility.value_, Eq(0));

  }
 } // namespace

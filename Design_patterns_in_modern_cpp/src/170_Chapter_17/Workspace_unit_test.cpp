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
  TEST(SimpleChatApp, Positive) {
    ChatRoom room;

    Person john{ "John" };
    Person jane{ "Jane" };
    room.join(&john);
    room.join(&jane);
    john.say("Hi room!");
    jane.say("Oh hey john!");
    Person simon{ "Simon" };
    room.join(&simon);
    simon.say("Hi to all!");
    jane.pm("Simon", "Glad you made it!");
  }

  TEST(BOOSTMediatorExample, Positive) {
    Game game;
    Player sam{ "Sam", game };
    Coach c_smith{ game };

    sam.score();
    sam.score();
    sam.score();
    sam.score();

  }
 } // namespace

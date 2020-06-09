// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <utility>

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

  TEST(SwitchStateMachine, Positive) {

    LightSwitch ls;
    ls.off();
    ls.on();
    ls.off();
  }

  TEST(PhoneStateMachine, Positive) {
    std::map<PhoneState, std::vector<std::pair<Trigger, PhoneState>>> rules;

    rules[PhoneState::off_hook] = {
      { Trigger::call_dailed, PhoneState::connecting },
      { Trigger::stop_using_phone, PhoneState::on_hold }
    };

    rules[PhoneState::connecting] = {
      { Trigger::hung_up, PhoneState::off_hook },
      { Trigger::call_connected, PhoneState::connected }
    };

    PhoneState currentState{ PhoneState::off_hook },
        exitState{ PhoneState::on_hook };
  }

  TEST(AVeryBloatedFSM, Positive) {
    boost::msm::back::state_machine<PhoneStateMachine> phone;
    auto info = [&]() {
      auto i = phone.current_state()[0];
      std::cout << "The phone is currently " << state_names[i] << "\n";
    };
    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();

    // try process_event here :)
    phone.process_event(CallDialed{});
  }

  } // namespace

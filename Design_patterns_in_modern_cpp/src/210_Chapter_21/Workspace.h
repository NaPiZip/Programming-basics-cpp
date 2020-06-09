// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "boost/msm/front/state_machine_def.hpp"
#include "boost/msm/front/functor_row.hpp"
#include "boost/msm/back/state_machine.hpp"


using std::string_literals::operator""s;

struct State;

class LightSwitch {
  State* state_;

public:
  LightSwitch();
  void set_state(State* state);

  void on();
  void off();
};

struct State {
  virtual void on(LightSwitch* ls);
  virtual void off(LightSwitch* ls);
};

struct OnState : State {
  OnState();
  void off(LightSwitch* ls) override;
};

struct OffState : State {
  OffState();
  void on(LightSwitch* ls) override;
};

enum class PhoneState {
  off_hook,
  connecting,
  connected,
  on_hold,
  on_hook
};

enum class Trigger {
  call_dailed,
  hung_up,
  call_connected,
  placed_on_hold,
  taken_off_hold,
  left_message,
  stop_using_phone
};


static std::vector<std::string> state_names{
  "off hook"s,
  "connecting"s,
  "connected"s,
  "on hold"s,
  "destroyed"s
};

// transitions/events
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : boost::msm::front::state_machine_def<PhoneStateMachine> {
  bool angry_{ false };

  struct OffHook : boost::msm::front::state<> {};
  struct Connected : boost::msm::front::state<> {};
  struct OnHold : boost::msm::front::state<> {};
  struct PhoneDestroyed : boost::msm::front::state<> {};

  struct Connecting : boost::msm::front::state<> {
    template <class Event, class FSM>
    void on_entry(Event const& evt, FSM&) {
      std::cout << "We are connecting.." << std::endl;
    }
    template <class Event, class FSM>
    void on_exit(Event const& evt, FSM&) {
      std::cout << "We are disconnectiong.." << std::endl;
    }
  };
  struct PhoneBeingDestroyed {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
      std::cout << "Phone breaks into a million pieces" << std::endl;
    }
  };
  struct CanDestroyPhone {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
      return fsm.angry_;
    }
  };
  // start, event, target, action, guard
  struct transition_table : boost::mpl::vector<
                                boost::msm::front::Row<OffHook, CallDialed, Connecting>,
                                boost::msm::front::Row<Connecting, CallConnected, Connected>,
                                boost::msm::front::Row<Connected, PlacedOnHold, OnHold>,
                                boost::msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed,
                                    PhoneBeingDestroyed, CanDestroyPhone>> {};

  // starting state
  typedef OffHook initial_state;

  template <class FSM, class Event>
  void no_transition(Event const& e, FSM&, int state) {
    std::cout << "No transition from state " << state_names[state] 
      << " on event " << typeid(e).name() << std::endl;
  }
};


#endif // _HEADER_WORKSPACE

// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>

LightSwitch::LightSwitch() {
  state_ = new OffState();
}

void LightSwitch::set_state(State* state) {
  this->state_ = state;
}

void LightSwitch::on() {
  state_->on(this);
}

void LightSwitch::off() {
  state_->off(this);
}

void State::on(LightSwitch* ls) {
  std::cout << "Light is already on\n";
}

void State::off(LightSwitch* ls) {
  std::cout << "Light is already off\n";
}

OnState::OnState() {
  std::cout << "Light turned on\n";
}

void OnState::off(LightSwitch* ls) {
  std::cout << "Switching light off...\n";
  ls->set_state(new OffState);
  delete this;
}

OffState::OffState() {
  std::cout << "Light turned off\n";
}

void OffState::on(LightSwitch* ls) {
  std::cout << "Switching light on...\n";
  ls->set_state(new OnState);
  delete this;
}

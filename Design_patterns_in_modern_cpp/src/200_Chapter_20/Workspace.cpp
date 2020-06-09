// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>

void ConsolePersonObserver::field_changed(Person& source, const std::string& field_name) {
  std::cout << "Person's " << field_name << " has changed to " << source.get_age() << ".\n";
}

int Person::get_age() const {
  return age_;
}

void Person::set_age(int value) {
  if (this->age_ == value)
    return;

  auto old_can_vote = get_can_vote();
  this->age_ = value;
  this->notify(*this, "age");

  if (old_can_vote != get_can_vote())
    notify(*this, "get_can_vote()");
}

bool Person::get_can_vote() const {
  return age_ >= 16;
}

void PersonWithSignal::set_age(int age) {

  if (this->age_ == age)
    return;
  this->age_ = age;
  property_changed_(*this, "age");
};
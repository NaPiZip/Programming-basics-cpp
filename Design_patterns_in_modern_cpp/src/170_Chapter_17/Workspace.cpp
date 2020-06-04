// Copyright 2019, Nawin

#include "Workspace.h"

#include <algorithm>
#include <iostream>
#include <iterator>

void ChatRoom::join(Person* p) {
  std::string join_msg = p->name_ + " joins the chat";
  broadcast("room", join_msg);
  p->room_ = this;
  people_.push_back(p);
}

void ChatRoom::broadcast(const std::string& origin, const std::string& message) {
  for (auto p : people_) {
    if (p->name_ != origin)
      p->receive(origin, message);
  }
}

void ChatRoom::message(const std::string& origin, const std::string& who, const std::string& message) {
  auto target = std::find_if(std::begin(people_), std::end(people_),
      [& who = static_cast<const std::string&>(who)](const Person* p) {
        return p->name_ == who;
      });
  if (target != std::end(people_))
    (*target)->receive(origin, message);
}

void Person::say(const std::string& message) const {
  room_->broadcast(name_, message);
}

void Person::pm(const std::string& who, const std::string& message) const {
  room_->message(name_, who, message);
}

void Person::receive(const std::string& origin, const std::string& message) {
  std::string s{ origin + ":\"" + message + "\"" };
  std::cout << "[" << name_ << "'a chat session] " << s << '\n';
  chat_log_.emplace_back(s);
}
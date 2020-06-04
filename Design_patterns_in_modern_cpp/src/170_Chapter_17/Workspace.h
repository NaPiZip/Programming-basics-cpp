// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <vector>

struct ChatRoom;

struct Person {
  std::string name_;
  ChatRoom* room_ = nullptr;
  std::vector<std::string> chat_log_;

  Person(const std::string& name) : name_{ name } {}

  void receive(const std::string& origin, const std::string& message);
  void say(const std::string& message) const;
  void pm(const std::string& who, const std::string& message) const;
};

struct ChatRoom {
  std::vector<Person*> people_;

  void join(Person* p);
  void broadcast(const std::string& orign, const std::string& message);
  void message(const std::string& origin, const std::string& who, const std::string& message);
};
#endif // _HEADER_WORKSPACE

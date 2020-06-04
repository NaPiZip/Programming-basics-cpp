// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <iostream>
#include <vector>

#include "boost/signals2/signal.hpp"

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

struct EventData {
  virtual ~EventData() = default;
  virtual void print() const = 0;
};

struct PlayerScoredData : EventData {
  std::string player_name_;
  int goals_scored_so_far_;
  PlayerScoredData(const std::string& player_name, int goals_scored_so_far) : player_name_{ player_name }, goals_scored_so_far_{ goals_scored_so_far } {}

  void print() const override;
};

struct Game {
  boost::signals2::signal<void(EventData*)> events; // observer
};

struct Player {
  std::string name_;
  int goals_scored_{0};
  Game& game_;
  Player(const std::string& name, Game& game) : name_{ name }, game_{ game } {}

  void score();
};

struct Coach {
  Game& game_;
  explicit Coach(Game& game) : game_{ game } {
    game_.events.connect([](EventData* e) {
      PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
      if (ps && ps->goals_scored_so_far_ < 3) {
        std::cout << "coach say: well done, " << ps->player_name_ << '\n';
      }
    });
  }
};

#endif // _HEADER_WORKSPACE


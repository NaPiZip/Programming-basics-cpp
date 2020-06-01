// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <iostream>
#include "boost/signals2/signal.hpp"

struct Creature {
  std::string name_;
  int attack_, defense_;

private:
  friend std::ostream& operator<<(std::ostream& os, const Creature& obj);
};

class CreatureModifier {
  CreatureModifier* next_{ nullptr };

protected:
  Creature& creature_;

public:
  explicit CreatureModifier(Creature& creature) : creature_{ creature } {}
  void add(CreatureModifier* cm);
  virtual void handle();
};

class DoubleAttackModifier : public CreatureModifier {
public:
  explicit DoubleAttackModifier(Creature& creature) : CreatureModifier{ creature } {}
  void handle() override;
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
  explicit IncreaseDefenseModifier(Creature& creature) : CreatureModifier{ creature } {}
  void handle() override;
};

class NoBonusesModifier : public CreatureModifier {
public:
  explicit NoBonusesModifier(Creature& creature) : CreatureModifier{ creature } {}
  void handle() override;
};

struct Query {
  std::string creature_name_;
  enum Argument { attack,
    defense } argument;
  int result;
};

struct Game {
  boost::signals2::signal<void(Query&)> queries;
};

class Creature2 {
  Game& game_;
  int attack_, defense_;  

public:  
  std::string name_;
  Creature2(Game& game, const std::string& name, int attack, int defense) : game_{ game }, name_{ name }, attack_{ attack }, defense_{defense} {};
  int get_attack() const;

private:
  friend std::ostream& operator<<(std::ostream& os, const Creature2& obj);
};

class CreatureModifier2 {
  Game& game_;
  Creature2& creature_;

public:
  CreatureModifier2(Game& game, Creature2& creature) : game_{ game }, creature_{ creature } {}
};

class DoubleAttackModifier2 : public CreatureModifier2 {
  boost::signals2::connection conn_;

public:
  DoubleAttackModifier2(Game& game, Creature2& creature) : CreatureModifier2{ game, creature } {
    conn_ = game.queries.connect([&](Query& q) 
      {
      if (q.creature_name_ == creature.name_ &&
          q.argument == Query::Argument::attack)
        q.result *= 2;
      }

    );
  };
  ~DoubleAttackModifier2() {
    conn_.disconnect();
  }
};
#endif // _HEADER_WORKSPACE

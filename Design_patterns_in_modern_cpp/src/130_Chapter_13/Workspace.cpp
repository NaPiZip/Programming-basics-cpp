// Copyright 2019, Nawin

#include "Workspace.h"


std::ostream& operator<<(std::ostream& os, const Creature& obj) {
  return os << obj.name_ << " a: " << obj.attack_ << " d: " << obj.defense_ << '\n';
}

void CreatureModifier::add(CreatureModifier* cm) {
  if (next_)
    next_->add(cm);
  else
    next_ = cm;
}
void CreatureModifier::handle() {
  if (next_)
    next_->handle();
}

void DoubleAttackModifier::handle() {
  creature_.attack_ *= 2;
  CreatureModifier::handle();
}

void IncreaseDefenseModifier::handle() {
  if (creature_.attack_ <= 2)
    creature_.defense_ += 1;
  CreatureModifier::handle();
}

void NoBonusesModifier::handle() {
  // nothing here;
}

std::ostream& operator<<(std::ostream& os, const Creature2& obj) {
  return os << obj.name_ << " a: " << obj.get_attack() << " d: " << obj.defense_ << '\n';
}

int Creature2::get_attack() const {
  Query q{ name_, Query::Argument::attack, attack_ };
  game_.queries(q);
  return q.result;
}
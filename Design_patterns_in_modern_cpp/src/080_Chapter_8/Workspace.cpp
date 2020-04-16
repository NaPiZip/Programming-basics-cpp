// Copyright 2019, Nawin

#include "Workspace.h"
#include <numeric>
#include <iostream>
int Creature::get_strength() const {
  return abilities_[str];
}
void Creature::set_strength(int strength) {
  abilities_[str] = strength;
}
double Creature::average() const {
  return sum() / count;
}

int Creature::sum() const {
  return std::accumulate(abilities_.begin(), abilities_.end(), 0);
}

void Circle::draw() {
  std::cout << "Drawing a circle\n";
}

void Group::draw() {
  std::cout << "Group " << name_ << " contains\n";
  for (auto&& o : objects_)
    o->draw();
}


void Neuron::connect_to(Neuron& other) {
  out_.push_back(&other);
  other.in_.push_back(this);
}

NeuronLayer::NeuronLayer(int count) {
  while (count-- > 0)
    emplace_back(Neuron{});
}
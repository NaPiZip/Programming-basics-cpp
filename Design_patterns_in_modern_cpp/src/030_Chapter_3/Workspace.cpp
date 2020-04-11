// Copyright 2019, Nawin

#include "Workspace.h"

#include <cmath>
#include <iostream>

Point PointFactory::NewCartesian(float x, float y) {
  return { x, y };
}

Point PointFactory::NewPolar(float r, float theta) {
  return { r * cos(theta), r * sin(theta) };
}


InnerPoint InnerPoint::PointFactory::NewCartesian(float x, float y) {
  return { x, y };
}

InnerPoint InnerPoint::PointFactory::NewPolar(float r, float theta) {
  return { r * cos(theta), r * sin(theta) };
}


void Tea::prepare(int volume) {
  std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon\n";
}

void Coffee::prepare(int volume) {
  std::cout << "Grind coffee beans, boil water, pour " << volume << "ml, add some milk\n";
}

std::unique_ptr<HotDrink> make_drink(std::string type) {
  std::unique_ptr<HotDrink> drink;

  if (type == "tea") {
    drink = std::make_unique<Tea>();
    drink->prepare(200);
  }
  else {
    drink = std::make_unique<Coffee>();
    drink->prepare(50);
  }
  return drink;
}

std::unique_ptr<HotDrink> CoffeeFactory::make() const {
  auto coffee = std::make_unique<Coffee>();
  coffee->prepare(50);
  return coffee;
}

std::unique_ptr<HotDrink> TeaFactory::make() const {
  auto tea = std::make_unique<Tea>();
  tea->prepare(200);
  return tea;
}

DrinkFactory::DrinkFactory() {
  hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
  hot_factories["tea"] = std::make_unique<TeaFactory>();
}
std::unique_ptr<HotDrink> DrinkFactory::make_drink(const std::string& name) {
  auto drink = hot_factories[name]->make();
  return drink;
}

DrinkWithVolumeFactory::DrinkWithVolumeFactory() {
  factories["tea"] = [] {
    auto tea = std::make_unique<Tea>();
    tea->prepare(200);
  return tea; };

  factories["coffee"] = [] {
    auto coffee = std::make_unique<Coffee>();
    coffee->prepare(50);
  return coffee; };
}

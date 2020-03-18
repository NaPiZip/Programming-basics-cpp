// Copyright 2019, Nawin

#include "Workspace.h"
#include <fstream>
#include <iostream>
using std::string_literals::operator ""s;

void Journal::AddLine(const std::string& entry) {
  notes_.push_back(std::to_string(notes_.size()) + ": "s + entry + "\n"s);
}

std::string Journal::GetLastLine(void) {
  return std::string(notes_.back());
}

Journal::iterator Journal::begin() {
  return notes_.begin();
}

Journal::const_iterator Journal::begin() const {
  return notes_.begin();
}

Journal::iterator Journal::end() {
  return notes_.end();
}

Journal::const_iterator Journal::end() const {
  return notes_.end();
}

size_t Journal::size() {
  return notes_.size();
}


void PersistenceManager::save(const Journal& j, const std::string& filename) {
  std::ofstream ofs(filename, std::ios::out);
  
  ofs << j.GetTitle() << '\n';
  for (auto c_it = j.begin(); c_it != j.end(); c_it++ ) 
  {
    ofs << *c_it;
  }
}

ProductFilter::Items ProductFilter::by_color(Items i, Color c) {
  Items results;
  for (const auto& element : i) {
    if (element->color_ == c)
      results.push_back(element);
  }
  return results;
}

bool ColorPredicate::operator()(Product* item) {
  return item->color_ == c_;
}

bool SizePredicate::operator()(Product* item) {
  return item->size_ == s_;
}


std::vector<Product*> GeneralFilter::filter(const std::vector<Product*>& items, predicate<Product>& p) {
  std::vector<Product*> results;
  for (const auto& element : items) {
    if (p(element))
      results.push_back(element);
  }
  return results;
}


std::vector<Product*> GeneralLambdaFilter::filter(const std::vector<Product*>& items, bool(*p)(const Product& i)) {
  std::vector<Product*> results;
  for (const auto& element : items) {
    if (p(*element))
      results.push_back(element);
  }
  return results;
}

Rectangle RectangleFactory::create_rectangle(int width, int height) {
  return Rectangle(width, height);
}

Rectangle RectangleFactory::create_square(int size) {
  return Square(size);
}
// Copyright 2019, Nawin

#include "Workspace.h"
#include <fstream>
#include <iostream>
using std::string_literals::operator ""s;

void Journal::AddLine(const std::string& entry) {
  notes_.push_back(std::to_string(notes_.size()) + ": "s + entry + "\n"s);
}

auto Journal::GetLastLine() -> std::string {
  return std::string(notes_.back());
}

auto Journal::begin() -> Journal::iterator {
  return notes_.begin();
}

auto Journal::begin() const -> Journal::const_iterator {
  return notes_.begin();
}

auto Journal::end() -> Journal::iterator {
  return notes_.end();
}

auto Journal::end() const -> Journal::const_iterator {
  return notes_.end();
}

auto Journal::size() -> size_t {
  return notes_.size();
}


void PersistenceManager::save(const Journal& j, const std::string& filename) {
  std::ofstream ofs(filename, std::ios::out);
  
  ofs << j.GetTitle() << '\n';
  for (const auto & c_it : j) 
  {
    ofs << c_it;
  }
}

auto ProductFilter::by_color(Items i, Color c) -> ProductFilter::Items {
  Items results;
  for (const auto& element : i) {
    if (element->color_ == c) {
      results.push_back(element);
}
  }
  return results;
}

auto ColorPredicate::operator()(Product* item) -> bool {
  return item->color_ == c_;
}

auto SizePredicate::operator()(Product* item) -> bool {
  return item->size_ == s_;
}


auto GeneralFilter::filter(const std::vector<Product*>& items, predicate<Product>& p) -> std::vector<Product*> {
  std::vector<Product*> results;
  for (const auto& element : items) {
    if (p(element)) {
      results.push_back(element);
}
  }
  return results;
}


auto GeneralLambdaFilter::filter(const std::vector<Product*>& items, bool(*p)(const Product& i)) -> std::vector<Product*> {
  std::vector<Product*> results;
  for (const auto& element : items) {
    if (p(*element)) {
      results.push_back(element);
}
  }
  return results;
}

auto RectangleFactory::create_rectangle(int width, int height) -> Rectangle {
  return Rectangle(width, height);
}

auto RectangleFactory::create_square(int size) -> Rectangle {
  return Square(size);
}
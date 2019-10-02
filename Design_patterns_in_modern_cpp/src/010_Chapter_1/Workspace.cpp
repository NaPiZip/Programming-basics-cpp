// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>

using std::string_literals::operator""s;

void Journal::AddLine(const std::string& entry) {
  static int count = 0;
  notes_.push_back(std::to_string(count++) + ": "s + entry);
}

std::string Journal::GetLastLine(void) {
  return std::string(notes_.back());
}

void PersistenceManager::save(const Journal& j, const std::string& filename) {
  
}
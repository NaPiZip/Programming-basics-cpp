// Copyright 2019, Nawin

#include "Workspace.h"
#include <fstream>

using std::string_literals::operator""s;

void Journal::AddLine(const std::string& entry) {
  notes_.push_back(std::to_string(notes_.size()) + ": "s + entry + "\n"s);
}

std::string Journal::GetLastLine(void) {
  return std::string(notes_.back());
}

Journal::iterator Journal::begin() {
  return notes_.begin();
}

Journal::iterator Journal::end() {
  return notes_.end();
}
size_t Journal::size() {
  return notes_.size();
}


void PersistenceManager::save(const Journal& j, const std::string& filename) {
  std::ofstream ofs(filename, std::ios::out);
}
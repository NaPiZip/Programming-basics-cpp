// Copyright 2019, Nawin

#include "Workspace.h"
#include <algorithm>

bool section_12_1::Entry::operator==(const Entry& e) const {
  return (this->name == e.name) && (this->number == e.number);
}

std::ostream& section_12_1::operator<<(std::ostream& os, const Entry& e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

std::istream& section_12_1::operator>>(std::istream& is, Entry& e) {
  // read { "name", number } pair. Note: formatted with { " ", and }
  char c, c2;
  if ((is >> c) && c == '{' && (is >> c2) && c2 == '"') {
    std::string name;
    while (is.get(c) && c != '"')
      name += c;

    if ((is >> c) && c == ',') {
      int number{ 0 };
      if ((is >> number >> c) && c == '}') {
        e = { name, number };
        return is;
      }
    }
  }
  is.setstate(std::ios_base::failbit);
  return is;
}


bool section_12_1::operator<(const Entry& rhs, const Entry& lhs) {
  return rhs.name < lhs.name;
}

bool section_12_2::contains_char(std::string_view sv, char c) {
  return std::find(sv.begin(), sv.end(), c) != sv.end();
}


std::vector<std::string_view::iterator>section_12_2::find_all(std::string_view sv, char c) {
  std::vector<std::string_view::iterator> matches;
  for (auto p = sv.begin(); p != sv.end(); ++p) {
    if (*p == c)
      matches.push_back(p);
  }
  return matches;
}

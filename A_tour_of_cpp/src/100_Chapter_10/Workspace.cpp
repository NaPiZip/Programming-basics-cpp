// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>

std::vector<int> section_10_4::read_ints(std::istream& is) {
  std::vector<int> results;
  for (int i ; (is >> i) ;)
    results.push_back(i);
  return results;
}


std::vector<int>section_10_4::read_ints(std::istream& is, const std::string& terminator) {
  std::vector<int> results;
  for (int i; is >> i;) {
    results.push_back(i);
  }

  if (is.eof())
    return results;

  if (is.fail()) {
    is.clear();
    is.unget();
    std::string s;
    if (is >> s && s == terminator)
      return results;
    is.setstate(std::ios_base::failbit);
  }

  return results;
}

bool section_10_5::Entry::operator==(const Entry& e) const {
  return (this->name == e.name) && (this->number == e.number);
}

std::ostream& section_10_5::operator<<(std::ostream& os, const Entry& e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

std::istream& section_10_5::operator>>(std::istream& is, Entry& e) {
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


bool section_10_8::is_open(std::fstream& f) {
  if (!f)
    return false;
  else
    return true;
}



std::ostringstream& section_10_10::print_directories(std::filesystem::path p) {
  using std::filesystem::directory_entry;
  using std::filesystem::directory_iterator;
  using std::filesystem::filesystem_error;

  std::ostringstream oss;

  try {
    if (is_directory(p)) {
      oss << p << ":\n";
      for (const directory_entry& x : directory_iterator{ p })
        oss << "  " << x.path() << '\n';
    }
  }
  catch (const filesystem_error & ex) {
    std::cerr << ex.what() << '\n';
  }

  return oss;
}

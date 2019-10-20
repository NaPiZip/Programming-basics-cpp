// Copyright 2019, Nawin

#include "Workspace.h"

bool section_11_1::Entry::operator==(const Entry& e) const {
  return (this->name == e.name) && (this->number == e.number);
}

std::ostream& section_11_1::operator<<(std::ostream& os, const Entry& e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

std::istream& section_11_1::operator>>(std::istream& is, Entry& e) {
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

int section_11_3::get_phone_number_by_name(std::list<section_11_1::Entry>& phone_book, std::string name) {
  for (const auto& element : phone_book) {
    if (element.name == name)
      return element.number;
  }
  return 0;
}

void section_11_3::remove_element_by_name(std::list<section_11_1::Entry>& phone_book, std::string name) {
  for (auto& it = phone_book.begin(); it != phone_book.end(); ++it) {
    if (it->name == name) {
      phone_book.erase(it);
      return;
    }
  }
}

int section_11_4::get_phone_number_by_name(std::map<std::string, int>& phone_book, std::string name) {
  return phone_book[name];
}


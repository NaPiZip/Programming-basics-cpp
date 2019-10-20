// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <list>
#include <map>
#include <string>
#include <ostream>
#include <sstream>


namespace section_11_1 {
struct Entry {
  std::string name;
  int number;
  bool operator==(const Entry& e) const;
};
std::ostream& operator<<(std::ostream& os, const Entry& e);
std::istream& operator>>(std::istream& is, Entry& e);
}  //  namespace section_11_1

namespace section_11_3 {
     int get_phone_number_by_name(std::list<section_11_1::Entry>& phone_book, std::string name);
     void remove_element_by_name(std::list<section_11_1::Entry>& phone_book, std::string name);
}  //  namespace section_11_3

namespace section_11_4 {
  int get_phone_number_by_name(std::map<std::string, int>& phone_book, std::string name);
}  //  namespace section_11_4

#endif  // _HEADER_WORKSPACE

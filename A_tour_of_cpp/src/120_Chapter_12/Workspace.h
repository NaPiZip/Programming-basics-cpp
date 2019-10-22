// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

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


#endif  // _HEADER_WORKSPACE

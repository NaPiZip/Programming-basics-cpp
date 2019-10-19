// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <vector>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>


namespace section_10_4 {

  std::vector<int> read_ints(std::istream& is);
  std::vector<int> read_ints(std::istream& is, const std::string& terminator);

}  //  namespace section_10_4

namespace section_10_5 {
struct Entry {
  std::string name;
  int number;
  bool operator==(const Entry& e) const;
};
std::ostream& operator<<(std::ostream& os, const Entry& e);
std::istream& operator>>(std::istream& is, Entry& e);
}  //  namespace section_10_5

namespace section_10_8 {
  bool is_open(std::fstream& f);
}  //  namespace section_10_8

namespace section_10_10 {
  std::ostringstream& print_directories(std::filesystem::path p);
}  //  namespace section_10_10
#endif  // _HEADER_WORKSPACE

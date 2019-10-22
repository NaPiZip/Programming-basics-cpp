// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <vector>
#include <string>
#include <string_view>
#include <ostream>
#include <sstream>


namespace section_12_1 {
struct Entry {
  std::string name;
  int number;
  bool operator==(const Entry& e) const;
};
std::ostream& operator<<(std::ostream& os, const Entry& e);
std::istream& operator>>(std::istream& is, Entry& e);

bool operator<(const Entry& rhs, const Entry& lhs);
}  //  namespace section_11_1

namespace section_12_2 {
  bool contains_char(std::string_view sv, char c);

  std::vector<std::string_view::iterator> find_all(std::string_view sv, char c);

  template<typename T>
  using Iterator = typename T::iterator;

  template<typename C, typename V>
  std::vector<Iterator<C>> find_all(C& c, V v) {
    std::vector<Iterator<C>> matches;
    for (auto p = c.begin(); p != c.end(); ++p) {
      if (*p == v)
        matches.push_back(p);
    }
    return matches;
  }

} //  namespace section_12_2


#endif  // _HEADER_WORKSPACE

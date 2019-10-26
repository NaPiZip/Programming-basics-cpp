// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <vector>
#include <list>
#include <memory>
#include <string>
#include <variant>
#include <iterator>

namespace section_13_2 {
std::unique_ptr<int> make_x(int i);

struct S {
  int i;
  std::string s;
  double d;
};
}  //  namespace section_13_2

namespace section_13_4 {
struct Record {
  std::string name;
  explicit Record(std::string& n) : name{ n } {}
};
}  //  namespace section_13_4

namespace section_13_5 {
std::variant<std::string, int> compose_message(bool return_int);
}  //  namespace section_13_5

namespace section_13_6 {
struct Event {
  std::vector<int> data = std::vector<int>(512);
};

}  //  namespace section_13_6


namespace section_13_9 {
  template<typename C>
  using Value_type = typename C::value_type;

  template<typename C>
  using Iterator_type = typename C::iterator;

  template<typename Iter>
  using Iterator_category = typename std::iterator_traits<Iter>::iterator_category;

  template<typename Ran>
  void sort_helper(Ran beg, Ran end, std::random_access_iterator_tag) {
    std::sort(beg, end);
  }
  template<typename For>
  void sort_helper(For beg, For end, std::forward_iterator_tag) {
    std::vector<Value_type<For>> v{ beg, end };
    std::sort(v.begin(), v.end());
    std::copy(v.begin(), v.end(), beg);
  }

  template<typename C>
  void sort(C& c) {
    using iter = Iterator_type<C>;
    sort_helper(c.begin(), c.end(), Iterator_category<iter>{});
  }
}  //  namespace section_13_9 

#endif  // _HEADER_WORKSPACE

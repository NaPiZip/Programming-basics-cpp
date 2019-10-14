// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <iostream>

namespace section_7_3 {

template<typename Iter, typename Val>
Val accumulate(Iter first, Iter last, Val val) {
  for (auto it = first; it != last; ++it) {
    val += *it;
  }
  return val;}


template<typename T>
void print(T& val) {
  std::cout << val << '\n';
}

template<typename T, typename ... Tail>
void print(T head, Tail... tail) {
  std::cout << head << ' ';
  print(tail...);
}

template<typename T, typename ... Tail>
void print2(T head, Tail... tail) {
  std::cout << head << ' ';
  if constexpr (sizeof ... (tail) > 0)
    print2(tail...);
}

}  //  namespace section_7_3

namespace section_7_4 {
template<typename ... T>
int sum(T... v) {
  return (v + ... );
}

template<typename ...T>
void print(T&&... args) {
  (std::cout << ... << args) << '\n';
}

}  // namespace section_7_4



#endif  // _HEADER_WORKSPACE

// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>
#include <string>
#include <iostream>
#include <type_traits>


namespace section_6_2 {


template<typename T, int N>
struct Buffer {
  using value_type = T;
  constexpr int size() { return N; }
  T data_[N];
};

template<typename T>
class Vector {
 private:
  T* element_{ nullptr };
  int sz_;
 public:
  explicit Vector(int sz);
  Vector(const Vector<T>& v);
  Vector(std::initializer_list<T> list);
  ~Vector() { if (element_) delete[] element_; }

  T& operator[](int i);
  const T& operator[](int i) const;

  void push_back(T val);

  T* begin();
  T* end();

  int size() const;
};

template<typename T>
class Vector2: public Vector<T> {
 public:
  using value_type = T;
  Vector2(std::initializer_list<T> list) : Vector<T>(list) {}

  template<typename Iter>
  Vector2(Iter b, Iter e);
};

#include "Workspace.hxx"

}  // namespace section_6_2


namespace section_6_3 {

template <typename T>
class Less_than {
  const T val_;
 public:
  explicit Less_than(const T& v) :val_{ v } {}
  bool operator()(const T& x) const { return x < val_; }
};

template<typename C, typename P>
int count(C& c, P pred) {
  auto cnt = 0;
  for (const auto& x : c) {
    if (pred(x))
      ++cnt;
  }
  return cnt;
}
}  //  namespace section_6_3

namespace section_6_4 {
template<typename T, typename T2>
constexpr bool Assignable = std::is_assignable<T&, T2>::value;

template<typename T>
void testAssignable() {
  static_assert(Assignable<T&, double>, "can't assingn a double");
  static_assert(Assignable<T&, std::string>, "can't assing a string");
}
}  //  namespace section_6_4

#endif  // _HEADER_WORKSPACE

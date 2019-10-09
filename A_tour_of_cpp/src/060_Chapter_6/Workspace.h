// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>
#include <string>
#include <iostream>



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
  explicit Vector(int) {}
  Vector(const Vector<T>& v);
  Vector(std::initializer_list<T> list);
  ~Vector() { if (element_) delete[] element_; }

  T& operator[](int i);
  const T& operator[](int i) const;

  T* begin();
  T* end();

  int size() const;
};

#include "Workspace.hxx"

template<typename T>
class Vector2 {
 public:
  using value_type = T;
  Vector2(std::initializer_list<T> list);
  template<typename Iter>
  Vector2(Iter b, Iter e);
};
}  // namespace section_6_2

#endif  // _HEADER_WORKSPACE

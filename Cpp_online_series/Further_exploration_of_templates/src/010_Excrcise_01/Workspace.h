// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <type_traits>
#include <iostream>

template <typename base, typename derived>
bool check_if_is_derived_type()
{
  return std::is_base_of<base, derived>::value;
}

template<typename T1, typename T2>
T1 add(T1 t1, T2 t2)
{
  static_assert(std::is_arithmetic<T1>::value);
  static_assert(std::is_arithmetic<T2>::value);

  static_assert(std::is_integral<T1>::value);
  static_assert(std::is_integral<T2>::value);

  return t1 + t2;
}

template<typename T>
void print(T t)
{
  std::cout << t;
}


template<typename T, typename... Args>
void print(T t,Args ... args)
{
  std::cout << t;
  print(args...);
}

#endif // _HEADER_WORKSPACE

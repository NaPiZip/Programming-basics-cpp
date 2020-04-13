// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <iostream>
#include <string>


struct Person {
  void greet();

  Person(std::string);
  ~Person();

  struct PersonImpl;
  PersonImpl* pimpl_;
};

#endif // _HEADER_WORKSPACE

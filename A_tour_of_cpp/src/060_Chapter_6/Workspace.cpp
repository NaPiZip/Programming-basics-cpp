// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>

section_5_2::Vector::Vector(std::initializer_list<double> list) :
  element_{ new double[list.size()] },
  sz_{ static_cast<int>(list.size()) } {
  int idx = 0;
  for (auto item : list) {
    element_[idx++] = item;
  }
}

section_5_2::Vector::Vector(const Vector& v) : 
  element_{ new double[v.sz_] },
  sz_{ v.sz_ } {
  for (auto idx = 0; idx != sz_; ++idx) {
    element_[idx] = v.element_[idx];
  }
}

section_5_2::Vector::Vector(Vector&& v) : element_{ v.element_ }, sz_{v.sz_} {
  v.element_ = nullptr;
  v.sz_ = 0;
  std::cout << "Moving shit! \n";
}

section_5_2::Vector& section_5_2::Vector::operator=(Vector&& v) {
  element_ = v.element_;
  sz_ = v.sz_;
  v.sz_ = 0;
  v.element_ = nullptr;

  return *this;
}


double& section_5_2::Vector::operator[](int i) {
  return element_[i];
}

int section_5_2::Vector::size() const {
  return sz_;
}

section_5_2::Vector section_5_2::returnVector() {
  // this return value will invoke the move constructor
  Vector res{ 1 ,2 ,3 };
  return res;
}
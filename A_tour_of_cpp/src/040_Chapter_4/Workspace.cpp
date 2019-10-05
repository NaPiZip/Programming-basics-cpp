// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>
#include <memory>
#include <stdexcept> 


double section_4_2::Complex::real() const {
  return real_;
}

void section_4_2::Complex::real(double re) {
  real_ = re;
}

double section_4_2::Complex::imag() const {
  return this->imag_;
}

void section_4_2::Complex::imag(double im) {
  imag_ = im;
}

section_4_2::Complex& section_4_2::Complex::operator+=(Complex z) {
  real_ += z.real();
  imag_ += z.imag();

  return *this;
}

section_4_2::Complex& section_4_2::Complex::operator-=(Complex z) {
  real_ -= z.real();
  imag_ -= z.imag();

  return *this;
}

section_4_2::Complex& section_4_2::Complex::operator*=(Complex z) {
  real_ *= z.real();
  imag_ *= z.imag();

  return *this;
}

section_4_2::Complex& section_4_2::Complex::operator/=(Complex z) {
  real_ /= z.real();
  imag_ /= z.imag();

  return *this;
}

bool section_4_2::operator==(const Complex& lhs, const Complex& rhs) {
  return (lhs.real() == rhs.real() && rhs.imag() == lhs.imag());
}

section_4_2::Vector::Vector(int s) : element{ new double[s] }, sz{ s } {
  for (int i = 0; i !=  s; ++i) {
    element[i] = 0;
  }
}

section_4_2::Vector::Vector(std::initializer_list<double> list) :
                                      element{new double[list.size()]},
                                      sz { static_cast<int>(list.size()) } {
  int idx = 0;
  for (auto item : list) {
    element[idx++] = item;
  }
}

void section_4_2::Vector::push_back(double n) {
  double* data = new double[sz + 1];
  std::copy(element, &element[sz], data);
  delete element;
  element = data;
  sz += 1;
  element[sz-1] = n;
}

double& section_4_2::Vector::operator[](int i) {
  return element[i];
}

int section_4_2::Vector::size() const {
  return sz;
}


void section_4_3::use(section_4_3::Container& c) {
  const int sz = c.size();
  for (int i = 0; i != sz; ++i) {
    std::cout << c[i] << '\n';
  }
}

double& section_4_3::List_container::operator[](int i) {
  
  for (auto it = ld.begin(); it != ld.end(); ++it) {
    if (!i--)
      return *it;
  }
  throw std::out_of_range{ "List container" };
}

void section_4_4::rotate_all(Shape* v, int angle) {
  v->rotate(angle);
}
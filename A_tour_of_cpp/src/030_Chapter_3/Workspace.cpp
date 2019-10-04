// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>

int my_code::Complex::real() const {
  return this->real_;
}

int my_code::Complex::imag() const {
  return this->imag_;
}

bool my_code::operator==(const Complex& lhs, const Complex& rhs) {
  return (lhs.real() == rhs.real() && rhs.imag() == lhs.imag());
}

my_code::Complex my_code::sqrt(const Complex&  number) {
  return Complex{ number.real() * number.real(),
                  number.imag() * number.imag() };
}

int my_code::main() {
  Complex z{ 1, 2 };
  auto z2 = sqrt(z);
  std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
  return 0;
}

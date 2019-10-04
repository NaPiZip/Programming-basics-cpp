// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

namespace my_code {

class Complex {
  int real_,
    imag_;
 public:
  Complex(int re, int im) : real_{ re }, imag_{ im } {}
  int real() const;
  int imag() const;
  bool friend operator==(const Complex& lhs, const Complex &rhs);
};

bool operator==(const Complex& lhs, const Complex& rhs);

Complex sqrt(const Complex& number);
int main();

}  //  namespace my_code

#endif  // _HEADER_WORKSPACE

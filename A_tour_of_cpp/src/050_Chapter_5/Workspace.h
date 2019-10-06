// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>

namespace section_5_2 {
class Vector {
 public:
  Vector() {} 
  explicit Vector(int) {}
  Vector(const Vector& v);  
  Vector(std::initializer_list<double> list);

  Vector(Vector&& v);
  Vector& operator=(Vector&& v);

  ~Vector() { if(element_) delete[] element_; }

  double& operator[](int i);

  int size() const;
 private:
   double* element_{nullptr};
  int sz_;
};
Vector returnVector();
}  // namespace section_5_2

#endif  // _HEADER_WORKSPACE

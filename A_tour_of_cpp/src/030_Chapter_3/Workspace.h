// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <variant>

namespace section_2_2 {

struct Vector {
  int sz = 0;
  double* element = nullptr;
};

void VectorInit(Vector& v, int s);

double ReadAndSum(int s);
}  // namespace section_2_2

namespace section_2_3 {

class Vector {
 public:
  explicit Vector(int s) :element{ new double[s] }, sz{ s } { }
  double& operator[](int i) { return element[i]; }
  int size() { return sz; }
 private:
  int sz;
  double* element;
};

}  // namespace section_2_3

namespace section_2_4 {

enum Type { ptr, num };

struct Node {
  double x;
};

union Value {
  Node* p;
    int i;
};

struct Entry {
  std::string name;
  Type t;
  Value v;  // use v.p if t==ptr; use v.i if t==num
};

struct EntryVariant {
  std::string name;
  std::variant < Node*, int > v;
};

}  // namespace section_2_4

#endif  // _HEADER_WORKSPACE

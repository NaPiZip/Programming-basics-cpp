// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>

namespace section_2_2 {

void VectorInit(Vector& v, int s) {
  v.element = new double[s];
  v.sz = s;
}

double ReadAndSum(int s) {
  Vector v;
  VectorInit(v, s);

  double sum = 0;
  for (int i = 0; i != s; ++i) {
    std::cin >> v.element[i];
    sum += v.element[i];
  }
  return sum;
}

}  // namespace section_2_2

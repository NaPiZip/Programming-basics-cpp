// Copyright 2019, Nawin

#include "Workspace.h"

std::unique_ptr<int>section_13_2::make_x(int i) {
  return std::unique_ptr<int>{new int{ i }};
}
// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <memory>
#include <string>

namespace section_13_2 {
  std::unique_ptr<int> make_x(int i);

  struct S {
    int i;
    std::string s;
    double d;
  };
}  //  namespace section_13_2



#endif  // _HEADER_WORKSPACE

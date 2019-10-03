// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

  #include <vector>

  void* operator new(size_t size);

  double vectorSumConst(const std::vector<double> && v);
  double vectorSum(std::vector<double> v);

#endif  // _HEADER_WORKSPACE

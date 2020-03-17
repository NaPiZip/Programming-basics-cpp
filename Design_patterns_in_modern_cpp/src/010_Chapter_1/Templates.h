#pragma once
#include <vector>

template <typename T>
struct predicate {
  virtual bool operator()(T* item) = 0;
};

template <typename T>
struct Filter {
  virtual std::vector<T*> filter(const std::vector<T*>& items, predicate<T>& p) = 0;
};

template <typename T>
struct LambdaFilter {
  virtual std::vector<T*> filter(const std::vector<T*>& items, bool(*p)(const T& i)) = 0;
};


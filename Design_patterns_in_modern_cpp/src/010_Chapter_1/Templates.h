#pragma once
#include <vector>

template <typename T>
struct predicate {
  virtual auto operator()(T* item) -> bool = 0;
};

template <typename T>
struct Filter {
  virtual auto filter(const std::vector<T*>& items, predicate<T>& p) -> std::vector<T*> = 0;
};

template <typename T>
struct LambdaFilter {
  virtual auto filter(const std::vector<T*>& items, bool(*p)(const T& i)) -> std::vector<T*> = 0;
};


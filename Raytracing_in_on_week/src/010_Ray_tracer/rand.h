#ifndef RANDH
#define RANDH

#include <random>

template<typename T>
inline T random() {
  static std::uniform_real_distribution<T> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}
#endif //  RANDH

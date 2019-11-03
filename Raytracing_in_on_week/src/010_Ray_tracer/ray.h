#ifndef RAYH
#define RAYH

#include "vec3.h"

template<typename T>
class ray {
public:
  ray() {}
  ray(const vec3<T>& a, const vec3<T>& b) { A = a; B = b; }
  vec3<T> origin() const { return A; }
  vec3<T> direction() const { return B; }
  vec3<T> point_at_paprameter(T t) const { return A + t*B; }

private:
  vec3<T> A, B;

};
#endif

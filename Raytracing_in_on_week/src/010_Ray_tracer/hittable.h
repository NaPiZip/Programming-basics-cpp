#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

template<typename T>
class material<T>;

template<typename T>
struct hit_record {
  T t;
  vec3<T> p, normal;
  material<T>* mat_ptr;
};

template<typename T>
class hittable {
public:
  virtual bool hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const = 0;
};

#endif // HITABLEH

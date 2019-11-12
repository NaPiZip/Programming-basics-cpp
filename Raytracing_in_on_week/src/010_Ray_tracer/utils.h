#ifndef UTILS
#define UTILS

#include "hittable_list.h"
#include "sphere.h"

#include <limits>


template <typename T>
T hitSphere(const vec3<T>& center, T radius, const ray<T>& r) {
  vec3<T> oc = r.origin() - center;
  T a = dot(r.direction(), r.direction()),
    b = 2.0 * dot(oc, r.direction()),
    c = dot(oc, oc) - radius * radius,
    discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
    return -1.0;
  else
    return (-b - sqrt(discriminant)) / (2.0*a);
}

template<typename T>
vec3<T> color(const ray<T> r) {
  T t = hitSphere(vec3<T>(0.0, 0.0, -1.0), 0.5, r);
  if (t > 0.0) {
    vec3<T> N = unit_vector(r.point_at_paprameter(t) - vec3<T>(0.0, 0.0, -1.0));
    return 0.5 * vec3<T>(N.x()+1, N.y()+1, N.z()+1);
  }
    

  vec3<T> unit_direction = unit_vector(r.direction());
  // -1.0 < y < 1.0 | +1 * 0.5
  // 0.0 < t < 1.0
  t = 0.5 * (unit_direction.y() + 1);
  return (1.0 - t) * vec3<T>(1.0, 1.0, 1.0) + t * vec3<T>(0.5, 0.7, 1.0);
}


template<typename T>
vec3<T> color(const ray<T>& r, hittable<T>* world) {
  hit_record<T> rec{};

  if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * color(ray(rec.p, target - rec.p), world);
  }
    else {
    vec3<T> unit_direction = unit_vector(r.direction());
     T t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3<T>(1.0, 1.0, 1.0) + t * vec3<T>(0.5, 0.7, 1.0);
  }
}
#endif

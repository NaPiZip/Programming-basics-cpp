#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

template<typename T>
class camera {
public:
  camera();
  ray<T> get_ray(T u, T v);

private:
  vec3<T> origin, lower_left_corner, horizontal, vertical;
};

#include "camera.hxx"

#endif //  CAMERAH

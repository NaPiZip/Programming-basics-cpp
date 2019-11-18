#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "corecrt_math_defines.h"

template<typename T = double>
class camera {
public:
  
  camera();
  camera(vec3<T>& lookfrom, vec3<T>& lookat, vec3<T>& vup, T vFov, T aspect);
  ray<T> get_ray(T u, T v);

private:
  vec3<T> origin, lower_left_corner, horizontal, vertical;
};

#include "camera.hxx"

#endif //  CAMERAH

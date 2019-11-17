
template<typename T>
camera<T>::camera(vec3<T>& lookfrom, vec3<T>& lookat, vec3<T>& vup, T vFov, T aspect) {
  vec3<T> u, v, w;
  T theta = vFov * M_PI / 180;
  T half_height = tan(theta / 2);
  T half_width = aspect * half_height;
  
  origin = lookfrom;
  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  lower_left_corner = origin - half_width * u - half_height * v - w;

  horizontal        = 2 * half_width* u ;
  vertical          = 2 * half_height * v;
  
}

template<typename T>
ray<T> camera<T>::get_ray(T u, T v) {
  return ray<T>(origin,
                lower_left_corner + u * horizontal + v * vertical - origin);
}

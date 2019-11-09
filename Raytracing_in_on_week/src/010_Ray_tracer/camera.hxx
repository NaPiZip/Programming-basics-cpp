template<typename T>
camera<T>::camera() {
  lower_left_corner = vec3(-2.0, -1.0, -1.0);
  horizontal        = vec3(4.0, 0.0, 0.0);
  vertical          = vec3(0.0, 2.0, 0.0);
  origin            = vec3(0.0, 0.0, 0.0);
}

template<typename T>
ray<T> camera<T>::get_ray(T u, T v) {
  return ray<T>(origin,
                lower_left_corner + u * horizontal + v * vertical - origin);
}

template<typename T>
vec3<T> metal<T>::reflect(const vec3<T>& v, const vec3<T>& n) const {
  return v - 2 * dot(v, n) * n;
}

template<typename T>
bool metal<T>::scatter(const ray<T>& r_in, const hit_record<T>& rec,
  vec3<T>& attenuation, ray<T>& scattered) const {
  vec3<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);;
  scattered = ray<T>(rec.p, reflected);
  attenuation = albedo;
  return (dot(scattered.direction(), rec.normal) > 0);
}

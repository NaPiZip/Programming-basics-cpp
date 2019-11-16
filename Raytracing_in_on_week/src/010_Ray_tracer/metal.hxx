
template<typename T>
metal<T>::metal(const vec3<T>& a, T f) : albedo(a) {
  if (f < 1)
    fuzz = f;
  else
    fuzz = 1;
}

template<typename T>
bool metal<T>::scatter(const ray<T>& r_in, const hit_record<T>& rec,
  vec3<T>& attenuation, ray<T>& scattered) const {
  vec3<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);;
  scattered = ray<T>(rec.p, reflected +fuzz * random_in_unit_sphere());
  attenuation = albedo;
  return (dot(scattered.direction(), rec.normal) > 0);
}

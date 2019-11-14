template<typename T>
bool lambertian<T>::scatter(const ray<T>& r_in, const hit_record<T>& rec,
  vec3<T>& attenuation, ray<T>& scattered) const {
  vec3<T> target = rec.p + rec.normal + random_in_unit_sphere<T>();
  scattered = ray<T>(rec.p, target - rec.p);
  attenuation = albedo;
  return true;
}

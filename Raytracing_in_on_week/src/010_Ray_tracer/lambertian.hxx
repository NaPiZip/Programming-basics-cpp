template<typename T>
bool lambertian<T>::scatter(const ray<T>& r_in, const hit_record<T>& rec,
  vec3<T>& attenuatiion, ray<T>& scatterd) const {
  vec3<T> target = rec.p + rec.normal + random_in_unit_sphere<T>();
  scatterd = ray<T>(rec.p, target - rec.p);
  attenuatiion = albedo;
  return true;
}

template<typename T>
bool dielectric<T>::refract(const vec3<T>& v, const vec3<T>& n, T ni_over_nt, vec3<T>& refracted) const {
  vec3<T> uv = unit_vector(v); 
  T dt = dot(uv, n);
  T  discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
  }
  else
    return false;
}


template<typename T>
T dielectric<T>::schlick(T cosine, T idx) const {
  T r0 = (1 - idx) / (1 + idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}


template<typename T>
bool dielectric<T>::scatter(const ray<T>& r_in, const hit_record<T>& rec,
  vec3<T>& attenuation, ray<T>& scattered) const {
  vec3<T> outward_normal,
          refracted;
  T ni_over_nt,
    reflect_prob,
    cosine;

  attenuation = vec3<T>(1.0, 1.0, 1.0);
 
  if (dot(r_in.direction(), rec.normal) > 0) {
    outward_normal = -rec.normal;
    ni_over_nt = ref_idx;
    cosine = ref_idx * dot(r_in.direction(), rec.normal)
      / r_in.direction().length();
  }
  else {
    outward_normal = rec.normal;
    ni_over_nt = 1.0 / ref_idx;
    cosine = - dot(r_in.direction(), rec.normal)
      / r_in.direction().length();
  }

  if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
    reflect_prob = schlick(cosine, ref_idx);
  }
  else {
    reflect_prob = 1.0;   
  }

  if (random<T>() < reflect_prob) {
    vec3<T> reflected = reflect(r_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
  }
  else {
    scattered = ray(rec.p, refracted);
  }
  return true;
}

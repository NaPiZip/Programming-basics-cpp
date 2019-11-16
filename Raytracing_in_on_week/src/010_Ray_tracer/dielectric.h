#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"

template<typename T = double>
class dielectric : public material {
public:
  dielectric(T ri) : ref_idx{ ri } {};
  virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec,
                      vec3<T>& attenuation, ray<T>& scattered) const override;
  bool refract(const vec3<T>& v, const vec3<T>& n, T ni_over_nt, vec3<T>& refracted) const;
  T schlick(T cosine, T idx) const;
private:  
  T ref_idx;
};

#include "dielectric.hxx"
#endif // DIELECTRICH

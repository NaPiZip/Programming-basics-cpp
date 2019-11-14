#ifndef METALH
#define METALH

#include "material.h"

template<typename T = double>
class metal: public material {
public:
  metal(const vec3<T>& a) : albedo(a) {}
  virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec,
                      vec3<T>& attenuation, ray<T>& scattered) const override;
  vec3<T> reflect(const vec3<T>& v, const vec3<T>& n) const;
private:
  
  vec3<T> albedo;
};

#include "metal.hxx"
#endif // METALH

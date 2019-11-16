#ifndef METALH
#define METALH

#include "material.h"

template<typename T = double>
class metal: public material {
public:
  metal(const vec3<T>& a, T f);
  virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec,
                      vec3<T>& attenuation, ray<T>& scattered) const override;
private:
  
  vec3<T> albedo;
  T fuzz;
};

#include "metal.hxx"
#endif // METALH

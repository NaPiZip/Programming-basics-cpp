#ifndef LAMBERTIAN
#define LAMBERTIAN

#include "material.h"

template<typename T = double>
class lambertian: public material<T> {
public:
  lambertian(const vec3<T>& a) : albedo(a) {}
  virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec,
                      vec3<T>& attenuatiion, ray<T>& scatterd) const override;
private:
  vec3<T> albedo;
};

#include "lambertian.hxx"
#endif // LAMBERTIAN

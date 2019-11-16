#ifndef MATERIALH
#define MATERIALH

#include "hittable.h"


class material {
public:
  virtual bool scatter(const ray<double>& r_in, const hit_record<double>& rec,
                      vec3<double>& attenuatiion, ray<double>& scatterd) const = 0;
  
  vec3<double> reflect(const vec3<double>& v, const vec3<double>& n) const;

};

#include "material.hxx"
#endif // MATERIALH

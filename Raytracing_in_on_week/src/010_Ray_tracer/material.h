#ifndef MATERIALH
#define MATERIALH

#include "hittable.h"


class material {
public:
  virtual bool scatter(const ray<double>& r_in, const hit_record<double>& rec,
                      vec3<double>& attenuatiion, ray<double>& scatterd) const = 0;
};

#endif // MATERIALH

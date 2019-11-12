#ifndef MATERIALH
#define MATERIALH

#include "hittable.h"

template<typename T>
class material {
public:
  virtual bool scatter(const ray<T>& r_in, const hit_record<T>& rec,
                      vec3<T>& attenuatiion, ray<T>& scatterd) const = 0;
};

#endif // MATERIALH

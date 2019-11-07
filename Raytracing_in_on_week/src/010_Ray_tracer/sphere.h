#ifndef SPHEREH
#define SPHEREH

#include"hittable.h"

template<typename T>
class sphere: public hittable<T> {
public:
  sphere();
  sphere(vec3<T> cen, T rad) : center{ cen }, radius{ rad } {}
  virtual bool hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const override;
private:
  vec3<T> center;
  T radius;
};

#include "sphere.hxx"


#endif // SPHEREH

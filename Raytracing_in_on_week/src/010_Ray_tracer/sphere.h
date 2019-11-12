#ifndef SPHEREH
#define SPHEREH

#include"hittable.h"
#include "rand.h"

template<typename T>
class sphere: public hittable<T> {
public:
  sphere();
  sphere(vec3<T> cen, T rad, material *m = nullptr) : center{ cen }, radius{ rad }, mat_ptr{m} {}
  virtual bool hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const override;
private:
  vec3<T> center;
  T radius;
  material* mat_ptr;
};

#include "sphere.hxx"


#endif // SPHEREH

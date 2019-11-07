#ifndef HITTABLE_LISTH
#define HITTABLE_LISTH

#include"hittable.h"

template<typename T>
class hittable_list: public hittable<T> {
public:
  hittable_list() { }
  hittable_list(hittable<T>** l, int n);
  virtual bool hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const override;
private:
  hittable<T>** list;
  int list_size;
};

#include "hittable_list.hxx"


#endif // HITTABLE_LISTH

template<typename T>
hittable_list<T>::hittable_list(hittable<T>** l, int n) {
  list = l;
  list_size = n;
}


template<typename T>
bool hittable_list<T>::hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const {
  hit_record<T> temp_rec;
  bool hit_anything = false;
  T closest_so_far = t_max;
  for (int i = 0; i < list_size; ++i) {
    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}


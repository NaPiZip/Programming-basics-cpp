template<typename T>
bool sphere<T>::hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const {
  vec3<T> oc = r.origin() - center;
  T a = dot(r.direction(), r.direction()),
    b = dot(oc, r.direction()),
    c = dot(oc, oc) - radius * radius,
    discriminant = b * b - a * c;
  
  if (discriminant > 0) {
    auto abc = [=, &rec](T val) {
      if (val < t_max && val >= t_min) {
        rec.t = val;
        rec.p = r.point_at_paprameter(val);
        rec.normal = (rec.p - center) / radius;
        return true;
      }
      else
        return false;
    };
    T tmp = (-b - sqrt(discriminant)) / (1.0 * a);
    return abc(tmp);
  }
    return false;
}


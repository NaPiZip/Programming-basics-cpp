template<typename T>
bool sphere<T>::hit(const ray<T> r, T t_min, T t_max, hit_record<T>& rec) const {
  vec3<T> oc = r.origin() - center;
  T a = dot(r.direction(), r.direction()),
    b = dot(oc, r.direction()),
    c = dot(oc, oc) - radius * radius;
    discriminant = b * b - a * c;

    if (discriminant > 0) {
      T temp = (-b - sqrt(discriminant)) / a;
      if (temp < t_max && temp > t_min) {
        rec.t = temp;
        rec.p = r.point_at_parameter(temp);
        rec.normal = (rec.p - center) / radius;
        return true
       }
      temp = (-b + sqrt(discriminant)) / a;
      if (temp < t_max && temp > t_min) {
        rec.t = temp;
        rec.p = r.point_at_paprameter(temp);
        rec.normal = (rec.p - center) / radius;
        return true;
      }
    }
    return false;
}


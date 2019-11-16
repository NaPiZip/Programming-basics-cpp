
vec3<double> material::reflect(const vec3<double>& v, const vec3<double>& n) const {
  return v - 2 * dot(v, n) * n;
}

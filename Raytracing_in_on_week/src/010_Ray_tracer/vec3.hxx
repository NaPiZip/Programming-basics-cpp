template<typename T>
inline vec3<T>& vec3<T>::operator+=(const vec3<T>& v) {
  e[0] = e[0] + v[0];
  e[1] = e[1] + v[1];
  e[2] = e[2] + v[2];
  return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator-=(const vec3<T>& v) {
  e[0] = e[0] - v[0];
  e[1] = e[1] - v[1];
  e[2] = e[2] - v[2];
  return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator*=(const vec3<T>& v) {
  e[0] = e[0] * v[0];
  e[1] = e[1] * v[1];
  e[2] = e[2] * v[2];
  return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator/=(const vec3<T>& v) {
  e[0] = e[0] / v[0];
  e[1] = e[1] / v[1];
  e[2] = e[2] / v[2];
  return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator*=(const T t) {
  e[0] = e[0] * t;
  e[1] = e[1] * t;
  e[2] = e[2] * t;
  return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator/=(const T t){
  e[0] = e[0] / t;
  e[1] = e[1] / t;
  e[2] = e[2] / t;
  return *this;
}


template<typename T>
inline T vec3<T>::length() const {
  return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

template<typename T>
inline T vec3<T>::squared_length() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

template<typename T>
inline void vec3<T>::make_unit_vector() {
  T k = 1.0 / length();
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
}

// global functions //

template <typename T>
 std::istream& operator>>(std::istream& is, vec3<T>& t) {
  is >> t[0] >> t[1] >> t[2];
  return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, vec3<T>& t) {
  os << "(x,y,z): " << t[0] << ", " << t[1] << ", " << t[2] << '\n';
  return os;
}

template <typename T>
inline T dot(const vec3<T>& v1, const vec3<T>& v2) {
  return  v1[0] * v2[0] +
          v1[1] * v2[1] +
          v1[2] * v2[2];
}

template <typename T>
inline T cross(const vec3<T>& v1, const vec3<T>& v2) {
  return vec3<T>( v1[1] * v2[2] - v1[2] * v2[1],
                  v1[2] * v2[0] - v1[0] * v2[2],
                  v1[0] * v2[1] - v1[1] * v2[0]);

}


template<typename T>
inline vec3<T> unit_vector(const vec3<T>& v) {
  return v / v.length();
}

template<typename T>
inline vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) {
  return vec3<T>(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

template<typename T>
inline vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) {
  return vec3<T>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

template<typename T>
inline vec3<T> operator*(const vec3<T>& v1, const vec3<T>& v2) {
  return vec3<T>(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

template<typename T>
inline vec3<T> operator/(const vec3<T>& v1, const vec3<T>& v2) {
  return vec3<T>(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

template<typename T>
inline vec3<T> operator*(T t, const vec3<T>& v) {
  return vec3<T>(t * v[0], t * v[1], t * v[2]);
}

template<typename T>
inline vec3<T> operator*( const vec3<T>& v, T t) {
  return vec3<T>(t * v[0], t * v[1], t * v[2]);
}

template<typename T>
inline vec3<T> operator/(T t, const vec3<T>& v) {
  return vec3<T>(t / v[0], t / v[1], t / v[2]);
}

template<typename T>
inline vec3<T> operator/(const vec3<T>& v, T t) {
  return vec3<T>(v[0] / t , v[1] / t, v[2] / t);
}

#ifndef HEADER_VEC3
#define HEADER_VEC3

#include <ostream>
#include <istream>
#include <math.h>

template <typename T>
class vec3
{
public:
  vec3() {}
  vec3(const vec3&);
  explicit vec3(T e0, T e1, T e2) : e{ e0, e1, e2 } {}

  inline T x() const { return e[0]; }
  inline T y() const { return e[1]; }
  inline T z() const { return e[2]; }
  inline T r() const { return e[0]; }
  inline T g() const { return e[1]; }
  inline T b() const { return e[2]; }

  inline const vec3& operator+() const { return *this; }
  inline vec3 operator-() const { return vec3<T>(-e[0], -e[1], -e[2]); }
  inline T operator[](int i) const { return e[i]; };
  inline T& operator[](int i) { return e[i]; }
  inline bool operator==(const vec3<T>& v) const {
    return  (this->e[0] == v[0]) &&
            (this->e[1] == v[1]) &&
            (this->e[2] == v[2]);
  }

  inline bool operator!=(const vec3<T>& v) const {
    return  (this->e[0] != v[0]) ||
      (this->e[1] != v[1]) ||
      (this->e[2] != v[2]);
  }
  
  inline vec3& operator+=(const vec3& );
  inline vec3& operator-=(const vec3& );
  inline vec3& operator*=(const vec3& );
  inline vec3& operator/=(const vec3& );
  inline vec3& operator*=(const T );
  inline vec3& operator/=(const T );

  inline T length() const;
  inline T squared_length() const;
  inline void make_unit_vector();

private:
  T e[3];
};

#include "vec3.hxx"

#endif  //  HEADER_VEC3

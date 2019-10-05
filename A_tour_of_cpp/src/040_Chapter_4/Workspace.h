// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>
#include <list>


namespace section_4_2 {

class Complex {
  double real_, imag_;
 public:
  Complex(double re, double im) : real_{ re }, imag_{ im } {}
  explicit Complex(double re) : real_{ re }, imag_{ 0 } {}
  Complex() : real_{ 0 }, imag_{ 0 } {}

  double real() const;
  void real(double re);
  double imag() const;
  void imag(double im);

  Complex& operator+=(Complex z);
  Complex& operator-=(Complex z);

  Complex& operator*=(Complex z);
  Complex& operator/=(Complex z);

  bool friend operator==(const Complex& lhs, const Complex &rhs);
};

bool operator==(const Complex& lhs, const Complex& rhs);

class Vector {
 public:
  explicit Vector(int);
  Vector(std::initializer_list<double> list);
  ~Vector() { delete element; }

  void push_back(double n);

  double& operator[](int i);
  int size() const;
 private:
  double* element;
  int sz;
};

}  //  namespace section_4_2

namespace section_4_3 {

class Container {
 public:
  virtual double& operator[](int) = 0;
  virtual int size() const = 0;
  virtual ~Container() {}
};

void use(Container& c);

class Vector_container : public Container {
 public:
  explicit Vector_container(int s) : v(s) {}
  ~Vector_container() override {}

  double& operator[](int i) override { return v[i]; }
  int size() const override { return v.size(); }
 private:
  section_4_2::Vector v;
};

class List_container : public Container {
 public:
  List_container() {}
  List_container(std::initializer_list<double> il) : ld{ il } {}
  ~List_container() {}
  double& operator[](int i) override;
  int size() const override { return ld.size(); }
 private:
  std::list<double> ld;
};

}  // namespace section_4_3

namespace section_4_4 {

template< typename T>
struct Point {
  T x{}, y{};
};


class Shape {
 public:
  virtual Point<double> center() const = 0;
  virtual void move(Point<double> pos) = 0;

  virtual void draw() const = 0;
  virtual void rotate(int angle) = 0;

  virtual ~Shape() {}
};

void rotate_all(Shape* v, int angle);

class Circle : public Shape {
 public:
  Circle(Point<double> p, int rad);
  Point<double> center() const override { return x; }
  void move(Point<double> pos) override { x = pos; }
  void draw() const override;
  void rotate(int) override {}
 private:
  Point<double> x;
  int r;
};



}  // namespace section_4_4

#endif  // _HEADER_WORKSPACE

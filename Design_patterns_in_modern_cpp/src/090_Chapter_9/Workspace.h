// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <type_traits>
#include <functional>
#include <iostream>

struct Shape {
  virtual std::string str() const = 0;
};


struct Circle : public Shape {
  float radius_;
  Circle() {}
  explicit Circle(float radius) : radius_{ radius } {}

  void resize(float);
  std::string str() const override;
};

struct Square : public Shape {
  float size_;
  Square() {}
  explicit Square(float a_) : size_{ a_ } {}

  void resize(float);
  std::string str() const override;
};


struct ColoredShape : public Shape {
  Shape& shape_;
  std::string color_;

  ColoredShape(Shape& shape, const std::string& color) : shape_{ shape }, color_{ color } {}
  std::string str() const override;
};

struct TransparentShape : public Shape {
  Shape& shape_;
  uint8_t transparency_;
  TransparentShape(Shape& shape, uint8_t transparency) : shape_{ shape }, transparency_{ transparency } {}
  std::string str() const override;
};

template <typename T>
struct NewColoredShape : T {
  static_assert(std::is_base_of<Shape, T>::value,
      "Template argument needs to be a type of shape");

  std::string color_;
  NewColoredShape() {}
  NewColoredShape(const std::string& color) : color_{ color } {}
  std::string str() const override {
    return T::str() + " has the color " + color_;
  }
};

template <typename T>
struct NewTransparentShape : T {
  static_assert(std::is_base_of<Shape, T>::value,
      "Template argument needs to be a type of shape");

  uint8_t transparency_;
  NewTransparentShape() {}
  NewTransparentShape(uint8_t transparency) : transparency_{ transparency } {}
  std::string str() const override {
    float transparency_in_percent = static_cast<float>(transparency_) / 255.f * 100.f;
    return T::str() + " has " + std::to_string(transparency_in_percent) + "% transparency";
  }
};


template <typename T>
struct NewColoredShape2 : T {
  static_assert(std::is_base_of<Shape, T>::value,
      "Template argument needs to be a type of shape");

  std::string color_;
  template <typename... Args>
  NewColoredShape2(const std::string& color, Args... args) : T(std::forward<Args>(args)...), color_{ color } {}
  std::string str() const override {
    return T::str() + " has the color " + color_;
  }
};

template <typename T>
struct NewTransparentShape2 : T {
  static_assert(std::is_base_of<Shape, T>::value,
      "Template argument needs to be a type of shape");

  uint8_t transparency_;
  template <typename... Args>
  NewTransparentShape2(uint8_t transparency, Args... args) : T(std::forward<Args>(args)...), transparency_{ transparency } {}
  std::string str() const override {
    float transparency_in_percent = static_cast<float>(transparency_) / 255.f * 100.f;
    return T::str() + " has " + std::to_string(transparency_in_percent) + "% transparency";
  }
};


struct Logger {
  std::function<void()> func_;
  std::string name_;

  Logger(const std::function<void()>& func, const std::string& name) : func_{ func }, name_{ name } {}
  void operator()();
};

template <typename Func>
struct DiffrentLogger {
  std::function<void()> func_;
  std::string name_;

  DiffrentLogger(const Func& func, const std::string& name) : func_{ func }, name_{ name } {}
  void operator()() {
    std::cout << "Entering " << name_ << '\n';
    func_();
    std::cout << "Exiting " << name_ << '\n';
  }
};

template <typename Func>
auto make_DiffrentLogger(Func func, const std::string& name) {
  return DiffrentLogger<Func>{ func, name };
}

// need partial specialization for this to work
template <typename>
struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)> {
  std::function<R(Args...)> func_;
  std::string name_;

  Logger3(std::function<R(Args...)> func, const std::string& name) : func_{ func }, name_{ name } {}

  R operator()(Args... args) {
    std::cout << "Entering " << name_ << '\n';
    R result = func_(args...);
    std::cout << "Exiting " << name_ << '\n';
    return result;
  }
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string& name) {
  return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}


#endif // _HEADER_WORKSPACE

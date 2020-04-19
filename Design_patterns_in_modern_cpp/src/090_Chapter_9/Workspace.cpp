// Copyright 2019, Nawin

#include "Workspace.h"

void Circle::resize(float factor) {
  radius_ *= factor;
}
std::string Circle::str() const {
  return "A circle of radius " + std::to_string(radius_);
}

void Square::resize(float factor) {
  size_ *= factor;
}
std::string Square::str() const {
  return "A square of edge length " + std::to_string(size_);
}

std::string ColoredShape::str() const {
  return shape_.str() + " has the color " + color_;
}

std::string TransparentShape::str() const {
  float transparency_in_percent = static_cast<float>(transparency_) / 255.f * 100.f;

  return shape_.str() + " has " + std::to_string(transparency_in_percent) + "% transparency";
}

void Logger::operator()() {
  std::cout << "Entering" << name_ << '\n';
  func_();
  std::cout << "Exiting" << name_ << '\n';
}
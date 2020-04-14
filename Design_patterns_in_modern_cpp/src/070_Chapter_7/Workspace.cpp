// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>

struct Person::PersonImpl {
  std::string name_;
  void greet(Person* p);
};
void Person::PersonImpl::greet(Person* p) {
  std::cout << "Helloooo " << p->pimpl_->name_ << "!!!\n";
}

Person::Person(std::string name) : pimpl_{ new PersonImpl{} } {
  pimpl_->name_ = name;
}

Person::~Person() {
  delete pimpl_;
}

void Person::greet() {
  pimpl_->greet(this);
}


void VectorRenderer::render_circle(float x, float y, float radius) {
  std::cout << "Drawing a vector circle of radius: " << radius << '\n';
}

void RasterRenderer::render_circle(float x, float y, float radius) {
  std::cout << "Rasterizing circle of radius: " << radius << '\n';
}

void Circle::draw() {
  renderer_.render_circle(x_, y_, radius_);
}
void Circle::resize(float factor) {
  radius_ *= factor;
}
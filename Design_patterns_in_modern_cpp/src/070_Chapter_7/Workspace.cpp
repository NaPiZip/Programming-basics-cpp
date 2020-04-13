// Copyright 2019, Nawin

#include "Workspace.h"

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

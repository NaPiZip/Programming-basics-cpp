// Copyright 2019, Nawin

#include "Workspace.h"

Contact& Contact::operator=(const Contact& other) {
  if (this == &other)
    return *this;
  name_ = other.name_;
  address_ = other.address_;
  return *this;
}

Contact EmployeeFactory::main_{ "", new Address{ "123 Est Dr", "London", 0 } };
Contact EmployeeFactory::aux_{ "", new Address{ "123B Est Dr", "London", 0 } };


std::unique_ptr<Contact> EmployeeFactory::NewEmployee(std::string name, int suite, const Contact& proto) {
  auto result = std::make_unique<Contact>(proto);
  result->name_ = name;
  result->address_->suite_ = suite;

  return result;
}
std::unique_ptr<Contact> EmployeeFactory::NewMainOfficeEmployee(std::string name, int suite) 
{
  return NewEmployee(name, suite, main_);
}
std::unique_ptr<Contact> EmployeeFactory::NewAuxOfficeEmployee(std::string name, int suite) 
{
  return NewEmployee(name, suite, aux_);
}

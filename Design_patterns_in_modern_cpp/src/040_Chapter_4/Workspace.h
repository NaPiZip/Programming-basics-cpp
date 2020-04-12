// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <memory>

struct Address {
  std::string street_, city_;
  int suite_;

  Address(const std::string& street, const std::string& city, int suite) : street_{ street }, city_{ city }, suite_{ suite } {}
};

struct Contact {
  std::string name_;
  Address* address_;

  Contact(const Contact& other) : name_{ other.name_ }, address_{ new Address{ *other.address_ } } {}
  Contact(const std::string& name, const Address* ad) : name_{ name }, address_{ new Address{ *ad } } {}
  Contact& operator=(const Contact& other);
};

struct EmployeeFactory {
  static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite);
  static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite);

  private:
  static Contact main_, aux_;
  static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, const Contact& proto);
};
#endif // _HEADER_WORKSPACE

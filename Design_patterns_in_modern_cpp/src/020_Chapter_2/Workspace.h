// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

struct HtmlElement {
  std::string name_;
  std::string text_;

  std::vector<HtmlElement> elements_;
  std::string str(int indent = 0) const;

  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text) : name_{ name }, text_{ text } {}

  friend struct HtmlBuilder;
};


struct HtmlBuilder {
  HtmlElement root_;

  HtmlBuilder(std::string root_name);
  HtmlBuilder& add_child(std::string child_name, std::string child_text);
  std::string str() const;
};


struct HtmlElemenUpdated : protected HtmlElement {
  const size_t indent_size = 2;

  static std::unique_ptr<HtmlBuilder> build(const std::string& s);

protected:
  HtmlElemenUpdated() : HtmlElement() {}
  HtmlElemenUpdated(const std::string& name, const std::string& text) : HtmlElement(name, text) {}
};

struct Tag {
  std::string name_;
  std::string text_;
  std::vector<Tag> children_;
  std::vector<std::pair<std::string, std::string>> attributes_;

  friend std::ostream& operator<<(std::ostream& os, const Tag& t);

protected:
  Tag(const std::string& name, const std::string& text) : name_{ name }, text_{ text } {}
  Tag(const std::string& name, const std::vector<Tag>& children) : name_{ name }, children_{ children } {}
};


struct P : Tag {
  explicit P(const std::string& text) : Tag{ "P", text } {}
  P(std::initializer_list<Tag> children) : Tag{ "p", children } {}
};

struct IMG : Tag {
  explicit IMG(const std::string& url) : Tag{ "img", "" } {
    attributes_.emplace_back(std::make_pair("src", url));
  }
};


 class PersonAddressBuilder;
 class PersonJobBuilder;
 class PersonBuilder;

class Person {
  //address
  std::string street_address_, post_code_, city_;

  //employment
  std::string company_name_, position_;
  int annual_income_ = 0;

public:
  Person() {}

  static PersonBuilder create();

  friend std::ostream& operator<<(std::ostream& os, const Person& obj);

  friend class PersonAddressBuilder;
  friend class PersonJobBuilder;
  friend class PersonBuilder;
};


class PersonBuilderBase {
protected:
  Person& person_;
  explicit PersonBuilderBase(Person& person) : person_{ person } {}

public:
  operator Person() {
    return std::move(person_);
  }

  PersonAddressBuilder lives(void) ;
  PersonJobBuilder works(void) ;
};

class PersonBuilder : public PersonBuilderBase {
  Person p_;

public:
  PersonBuilder() : PersonBuilderBase{ p_ } {}
};

class PersonAddressBuilder : public PersonBuilderBase {
  using self = PersonAddressBuilder;

public:
  explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{ person } {}
  self& at(std::string street_address) {
    person_.street_address_ = street_address;
    return *this;
  }
  self& with_postcode(std::string post_code) {
    person_.post_code_ = post_code;
    return *this;
  }

  self& in(std::string city) {
    person_.city_ = city;
    return *this;
  };
};

class PersonJobBuilder : public PersonBuilderBase {
  using self = PersonJobBuilder;

public:
  explicit PersonJobBuilder(Person& person) : PersonBuilderBase{ person } {}

  self& at(std::string company) {
    person_.company_name_ = company;
    return *this;
  }
  self& as_a(std::string pos) {
    person_.position_ = pos;
    return *this;
  }
  self& earning(int salary) {
    person_.annual_income_ = salary;
    return *this;
  }
};
#endif // _HEADER_WORKSPACE

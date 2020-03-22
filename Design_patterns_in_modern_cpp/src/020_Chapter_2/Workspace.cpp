// Copyright 2019, Nawin

#include "Workspace.h"

std::string HtmlElement::str(int indent) const {
  std::string result;
  for (auto e : elements_)
    result += e.name_ + e.text_;
  return result;
}


HtmlBuilder::HtmlBuilder(std::string root_name) {
  root_.name_ = root_name;
}
HtmlBuilder& HtmlBuilder::add_child(std::string child_name, std::string child_text) {
  HtmlElement e{ child_name, child_text };
  root_.elements_.emplace_back(e);
  return *this;
}
std::string HtmlBuilder::str() const {
  return root_.str();
}

std::unique_ptr<HtmlBuilder> HtmlElemenUpdated::build(const std::string& s) {
  return std::make_unique<HtmlBuilder>(s);
}

std::ostream& operator<<(std::ostream& os, const Tag& t) {
  os << '<' << t.name_ << '>' << t.text_<< std::endl;
  for (auto e : t.children_) {
    os << '<' << e.name_ << ' ';
    for (auto attrib : e.attributes_)
      os << attrib.first << "=\"" << attrib.second ;
    os << "\">" << std::endl;
  }
  os << "</" << t.name_ << '>' <<std::endl;
  return os;
}
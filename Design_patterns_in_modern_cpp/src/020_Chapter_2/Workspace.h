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
    attributes_.emplace_back(std::make_pair( "src", url));
  }
};
#endif // _HEADER_WORKSPACE

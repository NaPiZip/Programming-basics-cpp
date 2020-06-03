// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <iostream>
#include <string>
#include <memory>
#include <vector>

struct Token {
  enum class Type { integer,
    plus,
    minus,
    lparen,
    rparen } type_;
  std::string text_;

  explicit Token(Type type, const std::string& text) : type_{ type }, text_{ text } {}

  friend std::ostream& operator<<(std::ostream& os, const Token& obj);
};

std::vector<Token> lex(const std::string& input);

struct Element {
  virtual int eval() const = 0;
};

struct Integer : Element {
  int value_;
  explicit Integer(int value) : value_{ value } {}
  int eval() const override;
};

struct BinaryOperation : Element {
  enum class Type {addition, subtraction} type_;
  std::shared_ptr<Element> lhs_, rhs_;
  int eval() const override;
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens);


struct ast_element_visitor {};

struct ast_element {
  virtual ~ast_element() = default;
  virtual void accept(ast_element_visitor& visitor) = 0;
};

struct property : ast_element {
  std::vector<std::wstring> names_;
};
#endif // _HEADER_WORKSPACE

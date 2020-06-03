// Copyright 2019, Nawin

#include "Workspace.h"

#include <sstream>

std::ostream& operator<<(std::ostream& os, const Token& obj) {
  return os << '`' << obj.text_ << '`';
}


std::vector<Token> lex(const std::string& input) {
  std::vector<Token> results;
  for (int i = 0; i < input.size(); ++i) {
    switch (input[i]) {
    case '+':
      results.push_back(Token{ Token::Type::plus, "+" });
      break;
    case '-':
      results.push_back(Token{ Token::Type::minus, "-" });
      break;
    case '(':
      results.push_back(Token{ Token::Type::lparen, "(" });
      break;
    case ')':
      results.push_back(Token{ Token::Type::rparen, ")" });
      break;
    default:
      // number?
      std::ostringstream buffer;
      buffer << input[i];

      for (int j = i + 1; j < input.size(); ++j) {
        if (std::isdigit(input[j])) {
          buffer << input[j];
          i++;
        }
        else {
          results.push_back(Token{ Token::Type::integer, buffer.str() });
          break;
        }
      }
      break;
    }
  }
  return results;
}

int Integer::eval() const {
  return value_;
}

int BinaryOperation::eval() const {
  if (type_ == BinaryOperation::Type::addition)
    return lhs_->eval() + rhs_->eval();
  else
    return lhs_->eval() - rhs_->eval();
}

std::shared_ptr<Element> parse(const std::vector<Token>& tokens) {
  auto results = std::make_unique<BinaryOperation>();
  bool have_lhs = false;
  for (size_t i = 0; i < tokens.size(); ++i) {
    auto token = tokens[i];

    switch (token.type_) {
    case Token::Type::integer: {
      int value = std::stoi(token.text_);
      auto integer = std::make_shared<Integer>(value);
      if (!have_lhs) {
        results->lhs_ = integer;
        have_lhs = true;
      }
      else
        results->rhs_ = integer;
    } break;
    case Token::Type::plus:
      results->type_ = BinaryOperation::Type::addition;
      break;
    case Token::Type::minus:
      results->type_ = BinaryOperation::Type::subtraction;
      break;
    case Token::Type::lparen: {
      int j = i;
      for (; j < tokens.size(); ++j) {
        if (tokens[j].type_ == Token::Type::rparen)
          break;
      }
      std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
      auto element = parse(subexpression);
      if (!have_lhs) {
        results->lhs_ = element;
        have_lhs = true;
      }
      else
        results->rhs_ = element;
      i = j;
    }
    default:
      break;
    }
  }
  return results;
}

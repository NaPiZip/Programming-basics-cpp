// Copyright 2019, Nawin

#include "Workspace.h"

void func(Foo* foo){};
void func(Bar* bar){};

void CV_DoubleExpression::accept(CV_ExpressionVisitor* visitor) {
  visitor->visit(this);
}

void CV_AdditionExpression::accept(CV_ExpressionVisitor* visitor) {
  visitor->visit(this);
}

void CV_ExpressionPrinter::visit(CV_DoubleExpression* de) {
  _oss << de->value_;
}

void CV_ExpressionPrinter::visit(CV_AdditionExpression* ae) {
  _oss << "(";
  ae->left_->accept(this);
  _oss << "+";
  ae->right_->accept(this);
  _oss << ")";
}

void CV_ExpressionEvaluator::visit(CV_DoubleExpression* de) {
  _result = de->value_;
}

void CV_ExpressionEvaluator::visit(CV_AdditionExpression* ae) {
  ae->left_->accept(this);
  auto tmp = _result;
  ae->right_->accept(this);
  _result += tmp;
}
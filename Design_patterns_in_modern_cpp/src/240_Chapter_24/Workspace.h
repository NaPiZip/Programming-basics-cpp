// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <sstream>

struct Expression {
  virtual ~Expression() = default;
};

struct DoubleExpression : Expression {
  double value_;
  explicit DoubleExpression(double value) : value_{ value } {}
};

struct AdditionExpression : Expression {
  Expression *left_, *right_;

  AdditionExpression(Expression* const left, Expression* const right) : left_{ left }, right_{ right } {}
  ~AdditionExpression() {
    delete left_;
    delete right_;
  }
};

struct ExpressionPrinter {
  void print(Expression* e) {
    if (auto de = dynamic_cast<DoubleExpression*>(e))
      oss_ << de->value_;
    else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {

      oss_ << "(";
      print(ae->left_);
      oss_ << "+";
      print(ae->right_);
      oss_ << ")";
    }
  }
  std::string str() const {
    return oss_.str();
  }

protected:
  std::ostringstream oss_;
};

struct Foo;
struct Bar;

void func(Foo*);
void func(Bar*);

struct Stuff {
  virtual void call() = 0;
};

struct Foo : Stuff {
  void call() override {
    func(this);
  }
};

struct Bar : Stuff {
  void call() override {
    func(this);
  }
};

struct CV_ExpressionVisitor;

struct CV_Expression {
  virtual void accept(CV_ExpressionVisitor* visitor) = 0;
};

struct CV_DoubleExpression : CV_Expression {
  double value_;
  explicit CV_DoubleExpression(double value) : value_{ value } {}

  void accept(CV_ExpressionVisitor* visitor) override;
};


struct CV_AdditionExpression : CV_Expression {
  CV_Expression *left_, *right_;

  CV_AdditionExpression(CV_Expression* const left, CV_Expression* const right) : left_{ left }, right_{ right } {}
  ~CV_AdditionExpression() {
    delete left_;
    delete right_;
  }
  void accept(CV_ExpressionVisitor* visitor) override;
};

struct CV_ExpressionVisitor {
  virtual void visit(CV_DoubleExpression* de) = 0;
  virtual void visit(CV_AdditionExpression* ae) = 0;
};

struct CV_ExpressionPrinter : CV_ExpressionVisitor {
  std::ostringstream _oss;
  std::string str() const { return _oss.str(); };
  void visit(CV_DoubleExpression* de) override;
  void visit(CV_AdditionExpression* ae) override;
};

struct CV_ExpressionEvaluator : CV_ExpressionVisitor {
  double _result;
  void visit(CV_DoubleExpression* de) override;
  void visit(CV_AdditionExpression* ae) override;
};

template <typename Visitable>
struct Visitor {
  virtual void visit(Visitable& obj) = 0;
};
struct VisitorBase {
  virtual ~VisitorBase() = default;
};

struct AV_Expression {
  virtual ~AV_Expression() = default;
  virtual void accept(VisitorBase& obj) {
    using EV = Visitor<AV_Expression>;
    if (auto ev = dynamic_cast<EV*>(&obj))
      ev->visit(*this);
  }
};
#endif // _HEADER_WORKSPACE

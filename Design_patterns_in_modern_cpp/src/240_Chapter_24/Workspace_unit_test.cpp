// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <sstream>
#include <iostream>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;
using ::testing::Eq;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }
  TEST(ReflectiveVisitorPattern, Positive) {
    auto e = new AdditionExpression{
      new DoubleExpression{ 1 },
      new AdditionExpression{
          new DoubleExpression{ 2 },
          new DoubleExpression{ 3 } }
    };
    ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.str();
  }
  TEST(CommonVistiorExample) {
    auto e = new CV_AdditionExpression{
      new CV_DoubleExpression{ 1 },
      new CV_AdditionExpression{
          new CV_DoubleExpression{ 2 },
          new CV_DoubleExpression{ 3 } }
    };

    std::ostringstream oss;
    CV_ExpressionPrinter ep;
    ep.visit(e);
    std::cout << ep.str() << std::endl;
  }

  TEST(CommonVistiorWithEvaluatorExample) {
    auto e = new CV_AdditionExpression{
      new CV_DoubleExpression{ 1 },
      new CV_AdditionExpression{
          new CV_DoubleExpression{ 2 },
          new CV_DoubleExpression{ 3 } }
    };

    std::ostringstream oss;
    CV_ExpressionPrinter printer;
    CV_ExpressionEvaluator evaluator;
    printer.visit(e);
    evaluator.visit(e);
    std::cout << printer.str() << evaluator._result << std::endl;

    EXPECT_THAT(evaluator._result, Eq(6));
  }
} // namespace

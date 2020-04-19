// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <memory>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(DecoratorPattern, Scenario) {
    std::unique_ptr<Shape> shape = std::make_unique<Circle>(3.56f);
    std::cout << shape->str() << '\n';
  }

  TEST(DecoratorPattern, DynamicDecorator) {
    std::unique_ptr<ColoredShape> red_circle = std::make_unique<ColoredShape>(Circle(3.56f), "red");

    std::cout << red_circle->str() << '\n';
  }

  TEST(DecoratorPattern, DynamicDecoratorEnhancment) {
    std::unique_ptr<TransparentShape> demi_square = std::make_unique<TransparentShape>(Square(5), 85);

    std::cout << demi_square->str() << '\n';

    std::unique_ptr<ColoredShape> red_circle = std::make_unique<ColoredShape>(Circle(3.0f), "red");
    std::unique_ptr<TransparentShape> custom_circle = std::make_unique<TransparentShape>(*red_circle, 200);

    std::cout << custom_circle->str() << '\n';
  }

  TEST(DecoratorPattern, StaticDecoratorEnhancment) {
    std::unique_ptr<NewColoredShape<NewTransparentShape<Square>>> square = std::make_unique<NewColoredShape<NewTransparentShape<Square>>>("blue");
    square->size_ = 4;
    square->transparency_ = 80.f;
    square->resize(4);
    std::cout << square->str() << '\n';
  }

  TEST(DecoratorPattern, StaticDecoratorEnhancmentWithCtors) {
    std::unique_ptr<NewColoredShape2<NewTransparentShape2<Square>>> mixed_square = std::make_unique<NewColoredShape2<NewTransparentShape2<Square>>>("green", 50, 5.f);
    std::cout << mixed_square->str() << '\n';
  }

  float add(float x, float y) {
    return x + y;
  }

  TEST(DecoratorPattern, FunctionalDecorator) {
    Logger([]() { std::cout << "my func here\n"; }, "myfunc")();
    auto diffrent_logger = make_DiffrentLogger([]() { std::cout << "my func here\n"; }, "diffFunc");
    diffrent_logger();

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 4);
    std::cout << "Return value = " << result << '\n';
  }
} // namespace

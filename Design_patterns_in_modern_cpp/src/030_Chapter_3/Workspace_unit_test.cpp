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

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(FactoryClass, BasicIntro) {
    auto p = PointFactory::NewPolar(5, 2.14/2);
  }

  TEST(InnerFactoryClass, BasicIntro) {
    auto p = InnerPoint::Factory::NewPolar(5, 2.14 / 2);
  }

  TEST(AbstractFactory, BasicIntro) {
    auto tea    = make_drink("tea");
    auto coffee = make_drink("coffee");
  }

  TEST(AbstractFactory, FullFactories) {
    auto drink_factory = DrinkFactory();

    auto tea = drink_factory.make_drink("tea");
    auto coffee = drink_factory.make_drink("coffee");
  }

    TEST(FunctionalFactory, FullFactories) {
    auto drink_factory = DrinkWithVolumeFactory();

    auto tea = drink_factory.make_drink("tea");
    auto coffee = drink_factory.make_drink("coffee");
  }



} // namespace

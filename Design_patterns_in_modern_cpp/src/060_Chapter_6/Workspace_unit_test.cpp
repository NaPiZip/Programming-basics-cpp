// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
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

  TEST(BasicAdapterScenario, IntroExample) {
    std::vector<Point> points{
      { 1, 1 },
      { 2, 2 },
      { 3, 3 }
    };
    CPaintDC canvas;

    DrawPoints(canvas, points.begin(), points.end());
  }

  TEST(AdapterUsage, Example) {
    std::vector<std::shared_ptr<VectorObject>> vectorObjects{
      std::make_shared<VectorRectangle>(Point{ 10, 10 }, 100, 100),
      std::make_shared<VectorRectangle>(Point{ 30, 30 }, 60, 60)
    };
    CPaintDC canvas;

    for (auto& obj : vectorObjects) {
      for (auto& line : *obj) {
        std::cout << "\n--------------Drawing line-------------\n";
        LineToPointAdapter lpo{ line };
        DrawPoints(canvas, lpo.begin(), lpo.end());
      }
    }
  }

  TEST(AdapterUsage, TemporariesExample) {
    Point p{ 1, 1 };
    hash_value(p);
  }
} // namespace

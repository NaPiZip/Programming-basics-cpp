// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(Bridge, PimplIdiomExample) {
    Person nawin{ "Nawin" };
    nawin.greet();
  }

  TEST(Bridge, ABasicBridge) {
    std::shared_ptr<VectorRenderer> v_renderer = std::make_shared<VectorRenderer>();
    std::shared_ptr<RasterRenderer> r_renderer = std::make_shared<RasterRenderer>();

    std::unique_ptr<Circle> v_shape = std::make_unique<Circle>(*v_renderer, 1, 1, 1);
    std::unique_ptr<Circle> r_shape = std::make_unique<Circle>(*r_renderer, 1, 1, 1);
    v_shape->draw();
    r_shape->draw();
  }

} // namespace

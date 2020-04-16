// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <memory>
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

  TEST(Composite, ArrayPropertyExample) {
    Group root("root");
    std::shared_ptr<Circle> c1 = std::make_shared<Circle>();
    std::shared_ptr<Circle> c2 = std::make_shared<Circle>();
        
    root.objects_.push_back(c1);
    std::shared_ptr<Group> subgroup = std::make_shared<Group>("sub");
    subgroup->objects_.push_back(c2);
    root.objects_.push_back(subgroup);

    std::cout << "Refcount c1: " << c1.use_count() << '\n';

    root.draw();
  }

} // namespace

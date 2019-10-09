// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>
#include <utility>


void write(const section_6_2::Vector<std::string>& vs) {
  for (int i = 0; i != vs.size(); ++i) {
    std::cout << vs[i] << '\n';
  }
}

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(DeepCopyConstructor, Positive) {
    section_6_2::Vector<double> a{1, 2, 3};
    section_6_2::Vector<double> b(a);
    b[0] = 2;

    EXPECT_THAT(a[0], Ne(b[0]));
    EXPECT_THAT(b.size(), Eq(3));
  }

  TEST(TemplateExample, Positive) {
    section_6_2::Vector<std::string> a{ "this is some test"s };
    write(a);

    for (auto& i : a)
      std::cout << i << '\n';
  }

  TEST(ValueTemplate, Positive) {
    section_6_2::Buffer<char, 24> glob;
    EXPECT_THAT(glob.size(), Eq(24));
  }

  TEST(TemplateArgDeduction, Positive) {
    std::pair<int, double> p{ 1, 5.2 };
    auto p2 = std::make_pair(1, 5.2);
    std::pair p3 { 1, 5.2 };

    EXPECT_THAT(p, Eq(p2));
    EXPECT_THAT(p, Eq(p3));
  }

  }  // namespace

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
  TEST(VectorConstructorInt, Positive) {
    section_6_2::Vector<double> vec(4);
    EXPECT_THAT(vec.size(), Eq(4));
    EXPECT_THAT(vec[0], Eq(0));
    EXPECT_THAT(vec[1], Eq(0));
    EXPECT_THAT(vec[2], Eq(0));
    EXPECT_THAT(vec[3], Eq(0));

    section_6_2::Vector<double> vec_zero(0);
    EXPECT_THAT(vec_zero.size(), Eq(0));
  }
  TEST(DeepCopyConstructor, Positive) {
    section_6_2::Vector<double> a{1, 2, 3};
    section_6_2::Vector<double> b(a);
    b[0] = 2;

    EXPECT_THAT(a[0], Ne(b[0]));
    EXPECT_THAT(b.size(), Eq(3));
  }

  TEST(VectorPushBack, Positive) {
    section_6_2::Vector vec{ 1,2,3 };
    EXPECT_THAT(vec.size(), Eq(3));

    vec.push_back(4);
    EXPECT_THAT(vec.size(), Eq(4));
    EXPECT_THAT(vec[3], Eq(4));
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

    // Testing if inheretance actually worked as expected
    section_6_2::Vector2 a{ 1,2,3 };
    EXPECT_THAT(a.size(), Eq(3));
    EXPECT_THAT(a[0], Eq(1));

    section_6_2::Vector b{ 3,4,5 };
    //section_6_2::Vector2 c(b.begin(), b.end());
  }

  TEST(Functor, Positive) {
    section_6_3::Less_than a{ 23 };
    EXPECT_TRUE(a(3), true);
    section_6_2::Vector2 vec{ 1,1,1,10,10};    

    EXPECT_THAT(section_6_3::count(vec, section_6_3::Less_than{ 5 }), Eq(3));
    EXPECT_THAT(section_6_3::count(vec, section_6_3::Less_than{ 20 }), Eq(5));
  }


  }  // namespace

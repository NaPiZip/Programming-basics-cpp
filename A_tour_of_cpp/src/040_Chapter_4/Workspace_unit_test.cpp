// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>

namespace {

  using ::testing::Ne;
  using std::string_literals::operator""s;

  TEST(BasicTest, Positive) {
    EXPECT_THAT(2+3, 5);
  }

  TEST(ComplexBasicTest, Positive) {
    double abs_error = 0.001;
    section_4_2::Complex a{ 1, 2 },
                         b{ 1.4L },
                         c;

    EXPECT_NEAR(a.real(), 1L, abs_error);
    EXPECT_NEAR(a.imag(), 2L, abs_error);

    EXPECT_NEAR(b.real(), 1.4L, abs_error);
    EXPECT_NEAR(b.imag(), 0L, abs_error);

    EXPECT_NEAR(c.real(), 0L, abs_error);
    EXPECT_NEAR(c.imag(), 0L, abs_error);

    a.real(12.2);
    a.imag(-2.1);
    
    EXPECT_NEAR(a.real(), 12.2, abs_error);
    EXPECT_NEAR(a.imag(), -2.1, abs_error);

    a.real(1);
    a.imag(1);

    a += {3,3};

    EXPECT_NEAR(a.real(), 4, abs_error);
    EXPECT_NEAR(a.imag(), 4, abs_error);

    a -= {2, 2};

    EXPECT_NEAR(a.real(), 2, abs_error);
    EXPECT_NEAR(a.imag(), 2, abs_error);

    a *= a;

    EXPECT_NEAR(a.real(), 4, abs_error);
    EXPECT_NEAR(a.imag(), 4, abs_error);

    a /= a;

    EXPECT_NEAR(a.real(), 1, abs_error);
    EXPECT_NEAR(a.imag(), 1, abs_error);    
  }

  TEST(VectorBasisTest, Positive) {
    section_4_2::Vector a(5);

    EXPECT_THAT(a.size(), 5);

    for (int i = 0; i < a.size(); ++i) {
      EXPECT_THAT(a[i], 0);
    }

    a[0] = 2L;

    EXPECT_THAT(a[0], 2);
  }

  TEST(VectorInitList, Positive) {
    section_4_2::Vector a{1,2,3,4,5};

    EXPECT_THAT(a.size(), 5);
    for (int idx = 0; idx < a.size(); ++idx) {
      EXPECT_THAT(a[idx], idx + 1);
    }

    a.push_back(6);

    EXPECT_THAT(a.size(), 6);
    for (int idx = 0; idx < a.size(); ++idx) {
      EXPECT_THAT(a[idx], idx + 1);
    }
  }

  TEST(ContainerUseTest, Positive) {
    section_4_3::Vector_container a{ 4 };
    section_4_3::Container* vptr = &a;

    EXPECT_THAT(vptr->size(), 4);
    section_4_3::use(a);

    section_4_3::List_container b{ 1, 2, 3, 4 };
    section_4_3::List_container* lptr = &b;
    EXPECT_THAT(lptr->size(), 4);
    section_4_3::use(b);
  }

  }  // namespace

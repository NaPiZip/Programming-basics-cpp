// Copyright 2019, Nawin
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "vec3.h"

#include <iostream>

using std::string_literals::operator""s;
using ::testing::Eq;


namespace {

  TEST(Vec3GeneralTests, ShouldPass) {
    vec3 v1{ 1., 2., 3. },
         v2{ 1., 2., 3.};

    // const operator[]
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 2.0);
    EXPECT_DOUBLE_EQ(v1[2], 3.0);

    // operator[]
    v1[0] = 3.;
    v1[1] = 3.;
    v1[2] = 3.;
    EXPECT_DOUBLE_EQ(v1[0], 3.0);
    EXPECT_DOUBLE_EQ(v1[1], 3.0);
    EXPECT_DOUBLE_EQ(v1[2], 3.0);

    // operator+=
    v1 += v1;
    EXPECT_DOUBLE_EQ(v1[0], 6.0);
    EXPECT_DOUBLE_EQ(v1[1], 6.0);
    EXPECT_DOUBLE_EQ(v1[2], 6.0);

    // operator-=
    v1 -= v1;
    EXPECT_DOUBLE_EQ(v1[0], 0.0);
    EXPECT_DOUBLE_EQ(v1[1], 0.0);
    EXPECT_DOUBLE_EQ(v1[2], 0.0);

    // operator*=
    v1 = { 1., 2., 3. };
    v1 *= v1;
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 4.0);
    EXPECT_DOUBLE_EQ(v1[2], 9.0);

    // operator/=
    v1 /= v1;
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 1.0);
    EXPECT_DOUBLE_EQ(v1[2], 1.0);

    // operator t *=
    v1 *= 2.0;
    EXPECT_DOUBLE_EQ(v1[0], 2.0);
    EXPECT_DOUBLE_EQ(v1[1], 2.0);
    EXPECT_DOUBLE_EQ(v1[2], 2.0);

    // operator t /=
    v1 /= 2.0;
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 1.0);
    EXPECT_DOUBLE_EQ(v1[2], 1.0);

    // operator*/=
    v1 /= v1;
    EXPECT_DOUBLE_EQ(v1[0], 1.0);
    EXPECT_DOUBLE_EQ(v1[1], 1.0);
    EXPECT_DOUBLE_EQ(v1[2], 1.0);


    // x,y,z r,g,b functions
    EXPECT_DOUBLE_EQ(v1.x(), v1.r());
    EXPECT_DOUBLE_EQ(v1.y(), v1.g());
    EXPECT_DOUBLE_EQ(v1.z(), v1.b());

    // operator>>
    std::istringstream is{ "5. 6. 7."s };
    is >> v1;
    EXPECT_DOUBLE_EQ(v1[0], 5.0);
    EXPECT_DOUBLE_EQ(v1[1], 6.0);
    EXPECT_DOUBLE_EQ(v1[2], 7.0);

    // operator<<
    std::ostringstream oss;
    oss << v1;
    EXPECT_THAT(oss.str(), "(x,y,z): 5, 6, 7\n"s);

    // operator+ -
    v1 = { 1., 2., 3. };
    v2 = -v1;
    EXPECT_DOUBLE_EQ(-v1[0], v2[0]);
    EXPECT_DOUBLE_EQ(-v1[1], v2[1]);
    EXPECT_DOUBLE_EQ(-v1[2], v2[2]);
    
    v2 = +v1;
    EXPECT_DOUBLE_EQ(v1[0], v2[0]);
    EXPECT_DOUBLE_EQ(v1[1], v2[1]);
    EXPECT_DOUBLE_EQ(v1[2], v2[2]);

    // operator ==
    v1 = v2;
    EXPECT_THAT(v1, Eq(v2));

    // operator *
    v2 = v1 * v1;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 4);
    EXPECT_DOUBLE_EQ(v2[2], 9);


    // operator /
    v2 = v1 / v1;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 1);
    EXPECT_DOUBLE_EQ(v2[2], 1);

    // operator * t
    v2 = v1 * 2.;
    EXPECT_DOUBLE_EQ(v2[0], 2);
    EXPECT_DOUBLE_EQ(v2[1], 4);
    EXPECT_DOUBLE_EQ(v2[2], 6);

    // operator t * 
    v2 = 2. *v1 ;
    EXPECT_DOUBLE_EQ(v2[0], 2);
    EXPECT_DOUBLE_EQ(v2[1], 4);
    EXPECT_DOUBLE_EQ(v2[2], 6);
  
    // operator /
    v2 = 1. / v1;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 1./2.);
    EXPECT_DOUBLE_EQ(v2[2], 1./3.);

    // operator /
    v2 = v1 / 1.;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 2.);
    EXPECT_DOUBLE_EQ(v2[2], 3.);
  }

 
}  // namespace

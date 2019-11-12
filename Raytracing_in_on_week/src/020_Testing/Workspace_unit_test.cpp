// Copyright 2019, Nawin
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rand.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"

#include "hittable.h"
#include "hittable_list.h"

#include <iostream>
#include <memory>
#include <algorithm>

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
    v1 = vec3{ 1., 2., 3. };
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

    // lenght()
    v1 = vec3{ 2., 2., 1. };
    EXPECT_DOUBLE_EQ(v1.length(), 3.0);

    // squared_length()
    EXPECT_DOUBLE_EQ(v1.squared_length(), 9.0);

    // make_unit_vector()
    v1.make_unit_vector();
    EXPECT_DOUBLE_EQ(v1.length(), 1.0);

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
    v1 = vec3{ 1., 2., 3. };
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

  TEST(RayTest, Positive) {
    vec3 A{ 0.0, 0.0, 0.0 },
         B{ 0.0, 1.0, 0.0 };

    ray r(A, B);
    EXPECT_THAT(r.origin(), Eq(A));
    EXPECT_THAT(r.direction(), Eq(B));

    EXPECT_THAT(r.point_at_paprameter(1), Eq(A+B));
  }
  
  TEST(Hitrecord, Positive) {
    sphere s{ vec3{0.0, 0.0, -1.0}, 1.0 };
    ray r{ vec3{0.0, 0.0, 0.0}, vec3{0.0, 0.0, -1.0} };
    hit_record<double> record{};

    s.hit(r, 0.0, 1000.0, record);
    EXPECT_THAT(record.normal, Eq(vec3{ 0.0, 0.0, 1.0 }));
    EXPECT_THAT(record.p, Eq(vec3{ 0.0, 0.0, 0.0 }));
    EXPECT_THAT(record.t, Eq(0.0));
  };

  TEST(Hitlsit, Positive) {
    hittable<double>* list[2];
    list[0] = new  sphere{ vec3{0.0, 0.0, -1.0}, 1.0 };
    list[1] = new sphere{ vec3{0.0, 0.0, -1.0}, 1.0 };
    ray r{ vec3{0.0, 0.0, 0.0}, vec3{0.0, 0.0, -1.0} };

    hittable<double>* world = new hittable_list<double>(list, 2);
    
    hit_record<double> record{};
    EXPECT_TRUE(world->hit(r, 0.0, 1000.0, record));
    EXPECT_THAT(record.normal, Eq(vec3{ 0.0, 0.0, 1.0 }));
    EXPECT_THAT(record.p, Eq(vec3{ 0.0, 0.0, 0.0 }));
    EXPECT_THAT(record.t, Eq(0.0));
  }
  TEST(Rand, Positive) {
    std::vector v(1000, 0.0);

    for(auto& e: v)
      e = random<double>();
    
    std::sort(v.begin(), v.end());
    auto it = std::unique(v.begin(), v.end());
    EXPECT_THAT(it, Eq(v.end()));    
  }

  TEST(Camera, Positive) {
    camera cam;
    vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
    vec3 horizontal        = vec3(4.0, 0.0, 0.0);
    vec3 vertical          = vec3(0.0, 2.0, 0.0);
    vec3 origin            = vec3(0.0, 0.0, 0.0);

    EXPECT_THAT(cam.get_ray(0, 0).origin(),  origin);
    EXPECT_THAT(cam.get_ray(0, 0).direction(), lower_left_corner);
    
    EXPECT_THAT(cam.get_ray(0, 1).origin(), origin);
    EXPECT_THAT(cam.get_ray(0, 1).direction(), lower_left_corner + vertical);

    EXPECT_THAT(cam.get_ray(1, 0).origin(), origin);
    EXPECT_THAT(cam.get_ray(1, 0).direction(), lower_left_corner + horizontal);

    EXPECT_THAT(cam.get_ray(1, 1).origin(), origin);
    EXPECT_THAT(cam.get_ray(1, 1).direction(), lower_left_corner + horizontal +vertical);
  }

  TEST(RandSphere, Positive) {
    EXPECT_TRUE(random_in_unit_sphere() != random_in_unit_sphere());
  }

  TEST(lambertian, Positive){
    lambertian l(vec3{ 1.0, 1.0, 1.0 });
  }
   
}  // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <thread>
#include <functional>
#include <chrono>
#include <string>
#include <iostream>
#include <numeric>


namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(Simple, Positive) {
   EXPECT_TRUE(true);
 }

  TEST(Thread, Positive) {
    std::thread t1{ section_15_2::f };
    std::thread t2{ section_15_2::F() };

    t1.join();
    t2.join();
  }

  TEST(PassingArgs, Positive) {
    std::vector<double> some_data{ 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
    std::vector<double> diffrent_data{ 10, 11, 12, 13, 14, 15, 16 };

    std::thread t1{ section_15_3::f, std::ref(some_data) },
                t2{ section_15_3::F{diffrent_data} };

    t1.join();
    t2.join();
  }

  TEST(ReturningRes, Positve) {
    double  res1{0},
            res2{0},
            res3{0};
    std::vector<double> some_data{ 1, 2, 3, 4 , 5, 6, 7, 8, 9 };

    std::thread t1{ section_15_4::f,std::cref(some_data), &res1 },
                t2{ section_15_4::F{some_data, &res2} },
                t3{ [&]() {res3 = section_15_4::g(some_data); } };

    t1.join();
    t2.join();
    t3.join();

    EXPECT_THAT(res1, Eq(res2));
    EXPECT_THAT(res1, Eq(res3));
  }

  TEST(Mutex, Positive) {
    std::vector<double> some_data{ 1, 2, 3, 4 , 5, 6, 7, 8, 9 };
    std::vector<double> diffrent_data{ 10, 11, 12, 13, 14, 15, 16 };

    std::thread t1{ section_15_5::mutext_f, std::ref(some_data) },
                t2{ section_15_5::Mutext_F{diffrent_data} };

    t1.join();
    t2.join();
  }

  TEST(Waiting, Positive) {
    using std::chrono::high_resolution_clock;
    auto t0 = high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds{ 20 });
    auto t1 = high_resolution_clock::now();

    std::cout << "Time elapesd in nano sec: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << '\n';
  }
  
  TEST(Signals, Positive) {
    std::thread t1{ section_15_6::producer },
                t2{ section_15_6::consumer };

    t1.join();
    t2.join();
  }

  TEST(FutureAndPromism, Positive) {
    std::promise<std::string> prom;
    std::future<std::string> fut = prom.get_future();

    std::thread t1{ section_15_7::g, std::ref(fut) };

    section_15_7::f(prom);

    t1.join(); 
  }

  TEST(PackedTask, Positive) {
    std::vector<double> v{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    EXPECT_THAT(section_15_7::comp2(v), Eq(36));

    std::vector<double> v2(1001);
    std::iota(v2.begin(), v2.end(), 0.0);

    EXPECT_THAT(section_15_7::comp4(v2), Eq(500500));
  }


  }  // namespace

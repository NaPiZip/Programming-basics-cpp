// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <algorithm>
#include <mutex>
#include <string>
#include <iostream>
#include <bitset>
#include <any>
#include <chrono>

std::mutex m;

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(Simple, Positive) {
    std::unique_ptr<int> ptr = section_13_2::make_x(3);
    EXPECT_THAT(*ptr, Eq(3));
 }

  TEST(Bitsets, Positive) {
    std::bitset<5> bs1{"10010"};
    std::bitset<5> not_bs1= ~bs1;

    EXPECT_THAT(bs1, Eq(~not_bs1));
  }
  TEST(TupleAndSet, Positive) {
    using section_13_4::Record;

    std::vector<Record> v;
    v.reserve(4);
    v.emplace_back("Alice"s);
    v.emplace_back("Bob"s); 
    v.emplace_back("Carl"s);
    v.emplace_back("David"s);

    auto er = std::equal_range(v.begin(), v.end(),
      Record("Carl"s),
      [](const Record& r1, const Record& r2) {return r1.name < r2.name; });

    EXPECT_THAT((*er.first).name, Eq("Carl"s));
    EXPECT_THAT((*er.second).name, Eq("David"s));

    std::tuple<std::string, char, int> student{ "Nawin", 'A', 99 };

    EXPECT_THAT(std::get<std::string>(student), Eq("Nawin"));
    EXPECT_THAT(std::get<1>(student), Eq('A'));
    EXPECT_THAT(std::get<2>(student), Eq(99));   
   }

  TEST(Variant, Positive) {
    auto m = section_13_5::compose_message(true);
    if (std::holds_alternative <std::string>(m))
      EXPECT_EQ(std::get<std::string>(m), "Something"s);
    else 
      EXPECT_EQ(std::get<int>(m), 3);
  }

  TEST(Any, Positive) {
    std::any an_int = 1;

    try {
      EXPECT_EQ(std::any_cast<int>(an_int), 1);
      std::any_cast<std::string>(an_int);
    }
    catch (const std::bad_any_cast & e)
    {
      EXPECT_EQ(e.what(), "Bad any_cast"s);
    }
    an_int.reset();
    EXPECT_FALSE(an_int.has_value());
  }

  TEST(CustomAllocators, Positive) {
    constexpr int NUMBER_OF_DATA_ELEMENTS = 20;
    std::list<std::shared_ptr<section_13_6::Event>> q;

    auto t0 = std::chrono::high_resolution_clock::now();

    for (int n = 0; n < NUMBER_OF_DATA_ELEMENTS; ++n) {
      std::lock_guard lk{ m };
      q.emplace_back(std::make_shared<section_13_6::Event>());
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Elapesd time: "<< std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << '\n';
  }

  TEST(IteratorTraits, Positive) {
    std::vector v{ 1, 684, 3, 48, 12, 38 };
    std::list   l{ 5 , 6 , 54, 41658, 547 };

    section_13_9::sort(v);
    section_13_9::sort(l);

    for (const auto e : v)
      std::cout << e << ' ';
    
    std::cout << '\n';
    
    for (const auto e : l)
      std::cout << e << ' ';
  }


  }  // namespace

// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <bitset>


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
  }  // namespace

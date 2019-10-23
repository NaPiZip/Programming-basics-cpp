// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

#include <string>
#include <iostream>


namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(AVector, Positive) {
    std::list<section_12_1::Entry> unique_phone_book,
      unique_phone_book_v2(3);
    std::vector<section_12_1::Entry> phone_book = {
    {"David Hume", 123456},
    {"David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678} };

    std::sort(phone_book.begin(), phone_book.end());
    std::unique_copy(phone_book.begin(), phone_book.end(), std::back_inserter(unique_phone_book));
    std::unique_copy(phone_book.begin(), phone_book.end(), unique_phone_book_v2.begin());

    EXPECT_THAT(unique_phone_book, Eq(unique_phone_book_v2));

    for (auto element : unique_phone_book) {
      std::cout << element << '\n';
    }
  }

  TEST(BasicFind, Positive) {
    std::string test_sentence{ "Mary had a little lamb" };
    EXPECT_TRUE(section_12_2::contains_char("Nawin C Piffel"s,'C'));
    for (auto element : section_12_2::find_all(test_sentence, 'a'))
      EXPECT_THAT(*element, Eq('a'));

    std::list<int> ld{ 1, 1, 1, 2, 1, 2 };
    for (auto element : section_12_2::find_all(ld, 2))
      EXPECT_THAT(*element, Eq(2));

    std::vector<std::string> vs{ "red", "blue", "green", "green", "orange", "green" };
    for (auto element : section_12_2::find_all(vs, "green"))
      EXPECT_THAT(*element, Eq("green"));
  }

  TEST(StreamIter, Positive) {
    std::ostream_iterator<std::string> oo{ std::cout };
    //std::istream_iterator<std::string> ii{ std::cin };

    *oo = "Hello, ";
    ++oo;
    *oo = "world!";
  }

  TEST(Predicates, Positive) {
    std::map<std::string, int> m{ {"Nawin", 1}, {"Belen", 4}, {"JD", 7} };
    auto p = std::find_if(m.begin(), m.end(), section_12_5::Greater_than{ 4 });
    auto p2 = find_if(m.begin(), m.end(), [](const std::pair<std::string, int>& r) { return r.second > 4; });
    
    EXPECT_THAT(p->first, Eq( "JD"s));
    EXPECT_THAT(p->second, Eq(7));

   EXPECT_THAT(p2->first, Eq("JD"s));
   EXPECT_THAT(p2->second, Eq(7));
  }



  }  // namespace

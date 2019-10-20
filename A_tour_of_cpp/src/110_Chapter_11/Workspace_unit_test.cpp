// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <list>

#include <string>
#include <iostream>


namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(AVector, Positive) {
    std::ostringstream oss;
    std::vector<section_11_1::Entry> phone_book = {
    {"David Hume", 123456},
    {"Karl Popper", 234567},
    {"Bertrand Arthur William Russell", 345678} };

    for (const auto& element : phone_book) {
      oss << element << '\n';
    }
    std::cout << oss.str();
  }

  TEST(AList, Positive) {
    std::ostringstream oss;
    std::list<section_11_1::Entry> phone_book = {
     {"David Hume", 123456},
     {"Karl Popper", 234567},
     {"Bertrand Arthur William Russell", 345678} };

    for (const auto& element : phone_book) {
      oss << element << '\n';
    }
    std::cout << oss.str();
    EXPECT_THAT(section_11_3::get_phone_number_by_name(phone_book, "David Hume"s), Eq(123456));

    section_11_3::remove_element_by_name(phone_book, "David Hume"s);
    EXPECT_THAT(phone_book.size(), Eq(2));
    EXPECT_THAT(section_11_3::get_phone_number_by_name(phone_book, "David Hume"s), Eq(0));
  }

  TEST(AMap, Positive) {
    std::map<std::string, int> phone_book = {
     {"David Hume", 123456},
     {"Karl Popper", 234567},
     {"Bertrand Arthur William Russell", 345678} };

    EXPECT_THAT(section_11_4::get_phone_number_by_name(phone_book, "David Hume"s), Eq(phone_book["David Hume"s]));
  }

  }  // namespace

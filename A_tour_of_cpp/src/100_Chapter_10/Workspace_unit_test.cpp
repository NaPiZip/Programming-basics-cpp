// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <iostream>
#include <utility>
#include <filesystem>

namespace {

  using ::testing::Ne;
  using ::testing::Eq;
  using std::string_literals::operator""s;

  TEST(IostreamTest, Positive) {
    std::istringstream iss{ "10 23 123" };
    EXPECT_THAT(section_10_4::read_ints(iss), Eq(std::vector<int>{10, 23, 123}));
    /*
    for (auto el : section_10_4::read_ints(std::cin))
      std::cout << el << ' ';
      */
  }

  TEST(IostreanTestAdvanced, Positive) {
    std::istringstream iss_positive{ "1235 5 1  2 stop 3 8" },
                       iss_negative{"1 2 3 a 5 3"};

    EXPECT_FALSE(iss_positive.fail());
    EXPECT_FALSE(iss_negative.fail());

    EXPECT_THAT(section_10_4::read_ints(iss_positive, "stop"), Eq(std::vector{ 1235, 5, 1, 2 }));
    EXPECT_THAT(section_10_4::read_ints(iss_negative, "stop"), Eq(std::vector{ 1, 2, 3 }));

    EXPECT_FALSE(iss_positive.fail());
    EXPECT_TRUE(iss_negative.fail());
  }
  TEST(ReadWriteFromStd, Positive) {
    std::ostringstream oss;
    std::istringstream iss_positive{ "{\"Nawin\",  29}" },
                       iss_negative{ "{\"Nawin\"   29}" };

    EXPECT_FALSE(iss_positive.fail());
    EXPECT_FALSE(iss_negative.fail());

    section_10_5::Entry person_a{ "Nawin", 29 },
                        person_b;
    oss << person_a;
    EXPECT_THAT(oss.str(), Eq(std::string{ "{\"Nawin\", 29}"}));

    iss_positive >> person_b;
    EXPECT_THAT(person_a, Eq(person_b));
    EXPECT_FALSE(iss_positive.fail());

    iss_negative >> person_b;
    EXPECT_THAT(person_a, Eq(person_b));
    EXPECT_TRUE(iss_negative.fail());
  }
  TEST(GenericTests, Positive) {
    std::ostringstream oss;
    oss << std::scientific << 15.45;
    EXPECT_THAT(oss.str(), Eq(std::string{"1.545000e+01"}));
  }
  TEST(FilesystemTest, Positive) {
    std::filesystem::path cwd = std::filesystem::current_path(),
                          rel{"../../../src/100_Chapter_10"};

    EXPECT_TRUE(std::filesystem::exists(cwd / rel / std::filesystem::path{ "main.cpp" }));

    std::cout << section_10_10::print_directories(cwd).str();
  }
  }  // namespace

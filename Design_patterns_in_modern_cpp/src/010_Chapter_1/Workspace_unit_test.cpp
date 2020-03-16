// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <filesystem>
#include <fstream>
#include <string>


using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::Eq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2+3, 5);
  }

  TEST(JournalConstructor, Positive) {
    Journal obj("asdas"s);

    EXPECT_THAT(obj.GetTitle(), StartsWith("asd"));    
  }

  TEST(JournalAdd, Positive) {
    Journal obj("asdas"s);

    obj.AddLine("Something");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));

    obj.AddLine("Something else");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));
  }

  TEST(JournalSize, Positive) {
    Journal obj("asdas"s);

    obj.AddLine("Something");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));

    obj.AddLine("Something else");
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));

    EXPECT_THAT(obj.size(), 2);
  }


  TEST(JournalIterators, Positive) {
    std::vector<std::string> string_list = { "Something", "Something else" };

    Journal obj("asdas"s);

    obj.AddLine(string_list[0]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));
    obj.AddLine(string_list[1]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));

    for (Journal::iterator it = obj.begin(); it != obj.end(); ++it)
    {
      EXPECT_THAT(*it, HasSubstr(string_list[std::distance(obj.begin(), it)]));
    }
  }

  TEST(JournalSave, Positive) {
    std::string filename = "example.txt"s;
    std::vector<std::string> content_list = { "asada"s, "Something"s, "Something else"s};

    Journal obj(content_list[0]);

    obj.AddLine(content_list[1]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("0: "));
    obj.AddLine(content_list[2]);
    EXPECT_THAT(obj.GetLastLine(), StartsWith("1: "));
    
    PersistenceManager::save(obj, filename);

    EXPECT_THAT(std::filesystem::exists(filename), IsTrue);
    {
      std::ifstream ifs(filename, std::ifstream::in);
      std::string line;
      std::getline(ifs, line);
      EXPECT_THAT(line, Eq(content_list[0]));
      std::getline(ifs, line);
      EXPECT_THAT(line, StartsWith("0: "));
      std::getline(ifs, line);
      EXPECT_THAT(line, StartsWith("1: "));
    }

    EXPECT_THAT(std::filesystem::remove(filename), IsTrue);
  }


}  // namespace

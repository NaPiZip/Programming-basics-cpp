// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <memory>


using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
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

    for (auto it = obj.begin(); it != obj.end(); ++it) {
      EXPECT_THAT(*it, HasSubstr(string_list[std::distance(obj.begin(), it)]));
    }
  }

  TEST(JournalSave, Positive) {
    std::string filename = "example.txt"s;
    std::vector<std::string> content_list = { "asada"s, "Something"s, "Something else"s };

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
      EXPECT_THAT(line, StrCaseEq(content_list[0]));
      std::getline(ifs, line);
      EXPECT_THAT(line, StartsWith("0: "));
      std::getline(ifs, line);
      EXPECT_THAT(line, StartsWith("1: "));
    }

    EXPECT_THAT(std::filesystem::remove(filename), IsTrue);
  }

  TEST(BasicFilterNotOpenForExtensions, Positive) {
    std::vector<Product*> product_list = { new Product{ "Apple", Color::Green, Size::Small },
      new Product{ "Tree", Color::Green, Size::Large },
      new Product{ "House", Color::Blue, Size::Large } };

    auto filtered = ProductFilter::by_color(product_list, Color::Green);

    EXPECT_THAT(filtered.size(), 2);
    EXPECT_THAT(filtered[0]->name_, StrCaseEq("Apple"));
    EXPECT_THAT(filtered[1]->name_, StrCaseEq("Tree"));
  }

  TEST(BasicFilterOpenForExtensions, Positive) {
    std::vector<Product*> product_list = { new Product{ "Apple", Color::Green, Size::Small },
      new Product{ "Tree", Color::Green, Size::Large },
      new Product{ "House", Color::Blue, Size::Large } };

    GeneralFilter f;
    ColorPredicate pred_color(Color::Green);

    auto filtered_color = f.filter(product_list, pred_color);
    EXPECT_THAT(filtered_color.size(), 2);
    EXPECT_THAT(filtered_color[0]->name_, StrCaseEq("Apple"));
    EXPECT_THAT(filtered_color[1]->name_, StrCaseEq("Tree"));

    SizePredicate pred_size(Size::Small);
    auto filtered_size = f.filter(product_list, pred_size);
    EXPECT_THAT(filtered_size.size(), 1);
    EXPECT_THAT((filtered_size[0]->name_), StrCaseEq("Apple"));

    GeneralLambdaFilter lam;
    auto lambda = lam.filter(product_list, [](const Product& p) { return p.color_ == Color::Blue; });

    EXPECT_THAT(lambda.size(), 1);
    EXPECT_THAT((lambda[0]->name_), StrCaseEq("House"));
  }

  TEST(BasicinheritanceLiskovSub, BreakingTest) {
    Rectangle* r = &RectangleFactory::create_rectangle(5, 1);
    Rectangle* s = &RectangleFactory::create_square(5);

    EXPECT_NE(r->area(), s->area());

    r->set_height(5);

    EXPECT_EQ(r->area(), s->area());

    auto f = [](Rectangle* p) {
      int w = p->get_width();
      p->set_height(2);
      std::cout << "Expecting the area to be " << 2 * w << '\n';
      std::cout << "But actual is " << p->area() << '\n';
    };
    r->set_width(30);

    f(r);
    f(s);
  }


  TEST(InterfaceSegregation, Positive) {
  }

} // namespace

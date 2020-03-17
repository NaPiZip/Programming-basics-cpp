// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include "Templates.h"

#include <vector>
#include <string>


/* 
  Single Responsibility Principle (SRP)
*/
class Journal {
    std::string title_;
    std::vector<std::string> notes_;    
 public:
  explicit Journal(const std::string& title) : title_(title) {}
  const std::string& GetTitle() const { return title_; }
  void AddLine(const std::string& entry);
  std::string GetLastLine(void);

  // iterators
  using iterator = std::vector<std::string>::iterator;
  using const_iterator = std::vector<std::string>::const_iterator;
  iterator begin();
  const_iterator begin()const;
  iterator end();
  const_iterator end() const;
  size_t size();
};

class PersistenceManager {
public:
  static void save(const Journal& j, const std::string& filename);
};

enum class Color {Red, Green, Blue};
enum class Size {Small, Medium, Large};

struct Product {
  std::string name_;
  Color color_;
  Size size_;
};

struct ProductFilter {
  using Items = std::vector<Product*>;
  static Items by_color(Items i, Color c);
};

struct ColorPredicate : predicate<Product> {
  ColorPredicate(Color c) : c_{ c } {}
  bool operator()(Product* item) override;
  Color c_;
};

struct SizePredicate : predicate<Product> {
  SizePredicate(Size s) : s_{ s } {}
  bool operator()(Product* item) override;
  Size s_;
};

struct GeneralFilter : Filter<Product> {
  std::vector<Product*> filter(const std::vector<Product*>& items, predicate<Product>& p) override;
};

struct GeneralLambdaFilter : LambdaFilter<Product> {
  std::vector<Product*> filter(const std::vector<Product*>& items, bool(*p)(const Product& i)) override;
};

#endif  // _HEADER_WORKSPACE

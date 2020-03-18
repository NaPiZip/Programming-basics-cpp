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


class Rectangle {
protected:
  int width_, height_;

public:
  Rectangle(int width, int height) : width_{ width }, height_{ height } {}
  
  int get_width() const { return width_; }
  virtual void set_width(int width) { width_ = width; }

  int get_height() const { return height_; }
  virtual void set_height(int height) { height_ = height; }

  int area() const { return width_ * height_; }
  bool is_squared() const { return width_ == height_; }

};

class Square : public Rectangle {
public:
  Square(int size) : Rectangle(size, size) {}
  void set_width(int width) override { width_ = width; }
  void set_height(int height) override { height_= height; }

};

struct RectangleFactory {
  static Rectangle create_rectangle(int width, int height);
  static Rectangle create_square(int size);
};

struct Document;

struct IMachine {
  virtual void print(const std::vector<Document*>& docs) = 0;
  virtual void fax(const std::vector<Document*>& docs) = 0;
  virtual void scan(const std::vector<Document*>& docs) = 0;
};

struct MyFavouritePrinter : public IMachine {
  void print(const std::vector<Document*>& docs) override {}
  void  fax(const std::vector<Document*>& docs)  override {}
  void scan(const std::vector<Document*>& docs) override {}
};

struct IPrinter {
  virtual void print(const std::vector<Document*>& docs) = 0;
};

struct IScanner {
  virtual void scan(const std::vector<Document*>& docs) = 0;
};

struct IFax {
  virtual void fax(const std::vector<Document*>& docs) = 0;
};

struct Scanner : public IScanner {
  void scan(const std::vector<Document*>& docs) {}
};

struct IScanPrintMachine : public IScanner, IPrinter {};


struct Machine : public IScanPrintMachine {
  IPrinter* printer_;
  IScanner* scanner_;

  Machine(IPrinter& printer, IScanner& scanner) : printer_{ &printer }, scanner_{ &scanner } {}

  void print(const std::vector<Document*>& docs) override {
    printer_->print(docs);
  }
  void scan(const std::vector<Document*>& docs) override {
    scanner_->scan(docs);
  }
};

#endif  // _HEADER_WORKSPACE

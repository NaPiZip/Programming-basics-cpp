// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include "Templates.h"

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <string_view>
#include <memory>


/* 
  Single Responsibility Principle (SRP)
*/
class Journal {
  std::string title_;
  std::vector<std::string> notes_;

public:
  explicit Journal(std::string title) : title_(std::move(title)) {}
  [[nodiscard]] auto GetTitle() const -> const std::string& { return title_; }
  void AddLine(const std::string& entry);
  auto GetLastLine() -> std::string;

  // iterators
  using iterator = std::vector<std::string>::iterator;
  using const_iterator = std::vector<std::string>::const_iterator;
  auto begin() -> iterator;
  [[nodiscard]] auto begin() const -> const_iterator;
  auto end() -> iterator;
  [[nodiscard]] auto end() const -> const_iterator;
  auto size() -> size_t;
};

class PersistenceManager {
public:
  static void save(const Journal& j, const std::string& filename);
};

enum class Color { Red,
  Green,
  Blue };
enum class Size { Small,
  Medium,
  Large };

struct Product {
  std::string name_;
  Color color_;
  Size size_;
};

struct ProductFilter {
  using Items = std::vector<Product*>;
  static auto by_color(Items i, Color c) -> Items;
};

struct ColorPredicate : predicate<Product> {
  ColorPredicate(Color c) : c_{ c } {}
  auto operator()(Product* item) -> bool override;
  Color c_;
};

struct SizePredicate : predicate<Product> {
  SizePredicate(Size s) : s_{ s } {}
  auto operator()(Product* item) -> bool override;
  Size s_;
};

struct GeneralFilter : Filter<Product> {
  auto filter(const std::vector<Product*>& items, predicate<Product>& p) -> std::vector<Product*> override;
};

struct GeneralLambdaFilter : LambdaFilter<Product> {
  auto filter(const std::vector<Product*>& items, bool (*p)(const Product& i)) -> std::vector<Product*> override;
};


class Rectangle {
protected:
  int width_, height_;

public:
  Rectangle(int width, int height) : width_{ width }, height_{ height } {}

  [[nodiscard]] auto get_width() const -> int { return width_; }
  virtual void set_width(int width) { width_ = width; }

  [[nodiscard]] auto get_height() const -> int { return height_; }
  virtual void set_height(int height) { height_ = height; }

  [[nodiscard]] auto area() const -> int { return width_ * height_; }
  [[nodiscard]] auto is_squared() const -> bool { return width_ == height_; }
};

class Square : public Rectangle {
public:
  Square(int size) : Rectangle(size, size) {}
  void set_width(int width) override { width_ = width; }
  void set_height(int height) override { height_ = height; }
};

struct RectangleFactory {
  static auto create_rectangle(int width, int height) -> Rectangle;
  static auto create_square(int size) -> Rectangle;
};

struct Document;

struct IMachine {
  virtual void print(const std::vector<Document*>& docs) = 0;
  virtual void fax(const std::vector<Document*>& docs) = 0;
  virtual void scan(const std::vector<Document*>& docs) = 0;
};

struct MyFavouritePrinter : public IMachine {
  void print(const std::vector<Document*>& docs) override {}
  void fax(const std::vector<Document*>& docs) override {}
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
  void scan(const std::vector<Document*>& docs) override {}
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


struct ILogger {
  virtual ~ILogger() = default;
  virtual void log(const std::string& s) = 0;
};

class Reporting {
  ILogger& logger_;

public:
  Reporting(ILogger& logger) : logger_{ logger } {}
  void prepare_report() {
    logger_.log("Preparing the report");
  }
};


struct Engine {
  float volume{ 5.0 };
  int horse_power{ 400 };

  friend auto operator<<(std::ostream& os, const Engine& obj) -> std::ostream& {
    return os << "Volume: " << obj.volume
              << " HP: " << obj.horse_power;
  }
};

struct ConsoleLogger : ILogger {
  ConsoleLogger() {}
  void log(const std::string& s) override {
    std::cout << "Log: " << s << '\n';
  }
};


struct Car {
  std::unique_ptr<Engine> engine_;
  std::shared_ptr<ILogger> logger_;

  Car(std::unique_ptr<Engine>engine, const std::shared_ptr<ILogger>& logger) : engine_{std::move( engine) }, logger_{ logger } {
    logger->log("Making a car");
  }
};

#endif // _HEADER_WORKSPACE

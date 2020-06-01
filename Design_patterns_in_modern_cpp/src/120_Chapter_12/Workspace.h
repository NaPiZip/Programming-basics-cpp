// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <iostream>
#include <string>

struct BankAccount {
  void deposit(int);
};

template <typename T>
struct Property {
  T value_;
  Property(const T initial_value) {
    *this = initial_value;
  }

  operator T() {
    return value_;
  }

  T operator=(T new_value) {
    return value_ = new_value;
  }
};

struct Creature {
  Property<int> strength{ 4 };
  Property<int> agility{ 10 };
};


struct Image {
  std::string filename_;
  Image(const std::string& filename) : filename_{ filename } {};
  virtual void draw() = 0;
};

struct Bitmap : Image {
  Bitmap(const std::string& filename);
  void draw() override;
};

struct LazyBitmap : Image {
  LazyBitmap(const std::string& filename) : Image{ filename } {};
  ~LazyBitmap() { delete bmp_; }
  void draw() override;

private:
  Bitmap* bmp_{ nullptr };
};

struct Pingable {
  virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable {
  std::wstring ping(const std::wstring& message) override;
};
void tryit(Pingable& pp);
#endif // _HEADER_WORKSPACE

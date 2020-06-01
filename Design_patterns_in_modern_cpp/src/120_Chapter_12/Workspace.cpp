// Copyright 2019, Nawin

#include "Workspace.h"

void BankAccount::deposit(int amount) {
  // Do nothing
}


Bitmap::Bitmap(const std::string& filename) : Image{filename} {
  
  std::cout << "Loading image from file: " << filename << std::endl;
}

void Bitmap::draw() {
  std::cout << "Drawing image: " << filename_ << std::endl;
}

void LazyBitmap::draw() {
  if (!bmp_)
    bmp_ = new Bitmap(filename_);
  bmp_->draw();
}

std::wstring Pong::ping(const std::wstring& message) {
  return message + L" pong";
}


void tryit(Pingable& pp) {
  std::wcout << pp.ping(L"ping") << '\n';
}
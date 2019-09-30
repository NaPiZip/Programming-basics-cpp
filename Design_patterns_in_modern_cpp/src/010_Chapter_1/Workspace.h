// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

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
};

#endif  // _HEADER_WORKSPACE

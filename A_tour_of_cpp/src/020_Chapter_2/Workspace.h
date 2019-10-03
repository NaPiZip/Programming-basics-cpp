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
  void AddLine(const std::string& entry);
  std::string GetLastLine(void);

  // iterators
  using iterator = std::vector<std::string>::iterator;
  iterator begin();
  iterator end();
  size_t size();
};

class PersistenceManager {
  static void save(const Journal& j, const std::string& filename);
};

#endif  // _HEADER_WORKSPACE

// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING

#include <string>
#include <iostream>
#include <vector>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

using key = uint32_t;

struct User {
  User(const std::string& first_name, const std::string& last_name) : first_name_{ add(first_name) }, last_name_{ add(last_name) } {}
  const std::string& get_first_name() const;
  const std::string& get_last_name() const;

protected:
  key first_name_, last_name_;
  static key seed_;
  static boost::bimap<key, std::string> names_;
  static key add(const std::string& s);

private:
  friend std::ostream& operator<<(std::ostream& os, const User& obj);
};

struct User2 {
  boost::flyweight<std::string> first_name_, last_name_;
  User2(const std::string& first_name, const std::string& last_name) : first_name_{ first_name }, last_name_{ last_name } {}
};

class FormattedText {
  std::string plain_text_;
  bool* caps_;

public:
  explicit FormattedText(const std::string& plain_text) : plain_text_{ plain_text } {
    caps_ = new bool[plain_text.length()];
  }
  ~FormattedText() {
    delete[] caps_;
  }

  void capitalize(int start, int end);

private:
  friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj);
};

class BetterFormattedText {
public:
  struct TextRange {
    int start_, end_;
    bool capitalize;
    bool covers(int position) const {
      return position >= start_ && position <= end_;
    }
  };
  
  TextRange& get_range(int start, int end);
  BetterFormattedText(const std::string& s) : plain_text_{ s } {}

protected:
  std::string plain_text_;
  std::vector<TextRange> formatting_;

private:
  friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj);
};
#endif // _HEADER_WORKSPACE

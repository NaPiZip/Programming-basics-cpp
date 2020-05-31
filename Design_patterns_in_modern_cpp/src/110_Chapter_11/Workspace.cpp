// Copyright 2019, Nawin

#include "Workspace.h"

key User::seed_ = 0;
boost::bimap<key, std::string> User::names_ = {};

key User::add(const std::string& s) {
  auto it = names_.right.find(s);
  if (it == names_.right.end()) {
    names_.insert({ ++seed_, s });
    return seed_;
  }
  return it->second;
}

const std::string& User::get_first_name() const {
  return names_.left.find(first_name_)->second;
}

const std::string& User::get_last_name() const {
  return names_.left.find(last_name_)->second;
}

std::ostream& operator<<(std::ostream& os, const User& obj) {

  return os << "first name: "
            << obj.get_first_name()
            << " last name: "
            << obj.get_last_name();
}

 void FormattedText::capitalize(int start, int end) {
  for (int i = start; i <= end; ++i)
    caps_[i] = true;
}


std::ostream& operator<<(std::ostream& os, const FormattedText& obj) {
  std::string s;
  for (int i = 0; i < obj.plain_text_.length(); ++i) {
    char c = obj.plain_text_[i];
    s += (obj.caps_[i] == true ? std::toupper(c) : c);
  }
 
  return os << s;
}


BetterFormattedText::TextRange& BetterFormattedText::get_range(int start, int end) {
  formatting_.emplace_back(TextRange{ start, end });
  return *formatting_.rbegin();
}

std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj) {
  std::string s;
  for (size_t i = 0; i < obj.plain_text_.length(); i++) {
    auto c = obj.plain_text_[i];
    for (const auto& rng : obj.formatting_) {
      if (rng.covers(i) && rng.capitalize)
        c = std::toupper(c);
      s += c;
    }
  }
  return os << s;
}
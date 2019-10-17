// Copyright 2019, Nawin

#include "Workspace.h"
#include <regex>

using std::string_literals::operator""s;

std::string section_9_2::compose(const std::string& name, const std::string& domain) {
  return name + '@' + domain;
}

void section_9_2::appendNewLine(std::string& str) {
  str += '\n';
}


std::string section_9_3::cat(std::string_view sv1, std::string_view sv2) {
  std::string result(sv1.length() + sv2.length(), ' ');
  char* p = &result[0];
  for (char c : sv1)
    *p++ = c;

  for (char c : sv2)
    *p++ = c;

  return result;
}

void section_9_4::use(std::istream& in) {
  if (!in)
    std::cerr << "no file \n";

  std::regex pattern{ "[a-zA-Z]{2}\\s*\\d{5}" };
  int lineno = 0;

  for (std::string line; std::getline(in, line, '\n'); ) {
    ++lineno;
    std::smatch matches;
    if (std::regex_search(line, matches, pattern)) {
      std::cout << lineno << ": " << matches[0] << '\n';
      if (1 < matches.size() && matches[1].matched)
        std::cout << "\t" << matches[1] << '\n';
    }
  }
}

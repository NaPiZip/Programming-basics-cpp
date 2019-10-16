// Copyright 2019, Nawin

#include "Workspace.h"

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



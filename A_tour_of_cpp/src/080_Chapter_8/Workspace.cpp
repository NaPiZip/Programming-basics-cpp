// Copyright 2019, Nawin

#include "Workspace.h"

std::string section_9_2::compose(const std::string& name, const std::string& domain) {
  return name + '@' + domain;
}

void section_9_2::appendNewLine(std::string& str) {
  str += '\n';
}

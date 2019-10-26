// Copyright 2019, Nawin

#include "Workspace.h"

std::unique_ptr<int>section_13_2::make_x(int i) {
  return std::unique_ptr<int>{new int{ i }};
}

std::variant<std::string, int>section_13_5::compose_message(bool return_int) {
  if (return_int)
    return int{ 3 };
  else
    return std::string{ "Something" };
}

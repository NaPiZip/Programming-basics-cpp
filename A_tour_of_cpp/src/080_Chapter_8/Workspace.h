// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <string_view>

namespace section_9_2 {
std::string compose(const std::string& name, const std::string& domain);
void appendNewLine(std::string& str);
}  //  namespace section_9_2

namespace section_9_3 {

std::string cat(std::string_view sv1, std::string_view sv2);

} //  namespace section_9_3

#endif  // _HEADER_WORKSPACE

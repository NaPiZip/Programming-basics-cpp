// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <vector>

struct IBuffer {};

struct TableBuffer : IBuffer {  
  struct TableColumnSpec 
  {
    std::string header;
    int width;
    enum class TableColumnAlignment {
      Left,
      Center,
      Right
    } alignment;
  };

  TableBuffer(std::vector<TableColumnSpec> spec, int total_height) {
  }
};

#endif // _HEADER_WORKSPACE

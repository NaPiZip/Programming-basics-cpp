
#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include "gmock/gmock.h"
#include <iostream>
#include <vector>

#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(expression) {std::cout << expression << std::endl;}
#else
    #define DEBUG_PRINT(expression)
#endif

void swap(char & a, char &b);


class cBoard{
protected:
  static constexpr size_t cols = 3,
                          rows = 3;

   enum symbols: char{white= 'x', black = 'o', empty = ' '};
   /*
       |x|x|x| 3
       | | | | 2
       |o|o|o| 1
       A  B C
   */
   char currentPlayer;
   std::vector<std::vector<char>> board;

  bool is_in_range(std::string input);
  bool is_pice(std::string input);
public:
  cBoard():currentPlayer(symbols::white){  reset(); }; // Keyword constructor chaining
  cBoard(size_t _cols, size_t _rows){  reset(_cols, _rows); };
  void print();
  void reset(){reset(cols,rows);}
  void reset(size_t _cols, size_t _rows);
  void move(std::string stone, std::string pos);
};

#endif  /*_HEADER_WORKSPACE*/

#ifndef _HEADER_COUNTING_COLORED_SQUARES_
#define _HEADER_COUNTING_COLORED_SQUARES_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define DEBUG true
#define DEBUG_PRINT(str) if(DEBUG){cout << str << endl;}

int count_symbols_horizontal_and_vertical(vector<vector<char>> &field,
                                          int row, int column,
                                          char symbol);
bool has_same_symbol_as_neighbors(vector<vector<char>> &field,
                                          int row, int column,
                                          char symbol);


#endif //_HEADER_COUNTING_COLORED_SQUARES_

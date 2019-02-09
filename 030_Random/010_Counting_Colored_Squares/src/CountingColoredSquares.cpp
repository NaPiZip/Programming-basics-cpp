#include "CountingColoredSquares.hpp"

bool has_same_symbol_as_neighbors(vector<vector<char>> &field,
                  int row, int column,
                  char symbol)
{
  int nRows   = field.size();
  int nColums = field[0].size();

  if ((column >= 0 && column < nColums-1) &&
      (field[row][column]  == symbol &&
       field[row][column+1]== symbol))
    return true;
  else if ((column > 0 && column < nColums) &&
           (field[row][column] == symbol &&
           field[row][column-1]== symbol))
    return true;
  else if ((row >= 0 && row < nRows-1) &&
           (field[row][column]  == symbol &&
            field[row+1][column]== symbol))
    return true;
    else if ((row > 0 && row < nRows) &&
            (field[row][column]  == symbol &&
             field[row-1][column]== symbol))
        return true;
    else
      return false;
}

int count_symbols_horizontal_and_vertical(vector<vector<char>> &field,
                                          int row, int column,
                                          char symbol)
{
  int nRows   = field.size();
  int nColums = field[0].size();
  int sum = 0;

cout <<'-';
  if (column < 0 ||
      column >= nColums ||
      row < 0 ||
      row >= nRows)
    sum =  0;
  else if ( has_same_symbol_as_neighbors(field, row, column, symbol)){
    sum = +1 +
              count_symbols_horizontal_and_vertical(field, row, column+1, symbol)+
              count_symbols_horizontal_and_vertical(field, row, column-1, symbol) +
              count_symbols_horizontal_and_vertical(field, row+1, column, symbol) +
              count_symbols_horizontal_and_vertical(field, row-1, column, symbol);
  }
    sum = 0;
    /*
  if (column < 0 ||
      column >= nColums ||
      row < 0 ||
      row >= nRows)
    return 0;
  else if(field[column][row] == symbol &&
          (field[column+1][row] == symbol ||
           field[column-1][row] == symbol ||
           field[column][row+1] == symbol ||
           field[column][row-1] == symbol))
    sum = 1;
  else if(column < nColums) // -->
    sum += count_symbols_horizontal_and_vertical(field, row, column+1, symbol);
  else if(row >= 0) // down
    sum += count_symbols_horizontal_and_vertical(field, row+1, column, symbol);
  else if(column >= 0) // <--
    sum += count_symbols_horizontal_and_vertical(field, row, column-1, symbol);
  else if(row < nRows)// up
    sum += count_symbols_horizontal_and_vertical(field, row-1, column, symbol);
  else
    return 0;
*/
  return sum;
}

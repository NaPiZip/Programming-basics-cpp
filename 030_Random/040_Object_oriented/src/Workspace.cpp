#include "Workspace.hpp"
#include "gtest/gtest.h"

using ::testing::AtLeast;

void swap(char & a, char &b){
  char tmp = a;
  a = b;
  b = tmp;
}

TEST(Swap, singleTest){
  char a = 'a',
       b = 'b';
  swap(a,b);
  EXPECT_EQ(a, 'b');
  EXPECT_EQ(b, 'a');
}


void cBoard::reset(size_t _cols, size_t _rows){
  std::cout << "Ctor " <<_cols << ' '<< _rows <<std::endl;
  for(size_t i = 0; i< _rows; i++){
    if(i == 0)
      board.push_back(std::vector<char> (_cols,symbols::white));
    else if(i == rows -1)
      board.push_back(std::vector<char> (_cols,symbols::black));
    else
      board.push_back(std::vector<char> (_cols,symbols::empty));
  }
  std::cout << board.size() << " " << board[0].size();
}

void cBoard::print(){
  std::cout << std::endl;
  for(auto row:board){
    for(auto col:row){
      std::cout << '|'<< col;
    }
    std::cout<<'|' <<std::endl;
  }
}

bool cBoard::is_in_range(std::string input){
  bool inBoundCol = false,
       inBoundsRow = false;

  if(!input.size())
  {
    std::cout << "Error: Input empty." << std::endl;
    return false;
  }
  else if(input.size() >2){
    std::cout << "Error: Input " << input << " to long." << std::endl;
    return false;
  }
  if(reinterpret_cast<int>(std::toupper(input[0]) - 'A') >= 0 &&
     reinterpret_cast<int>(std::toupper(input[0]) - 'A') <= board[0].size())
    inBoundCol = true;
  if(reinterpret_cast<int>(input[0] - '0') >0 &&
     reinterpret_cast<int>(input[0] - '0') >=board.size())
    inBoundsRow = true;

  return inBoundCol && inBoundCol;
}
void cBoard::move(std::string stone, std::string pos)
{

}


 TEST(cBoard, randomStuff){
   class tester:public cBoard{
   public:
      void check_size(size_t _row, size_t _col) {
        EXPECT_EQ(board.size(),_col);
        EXPECT_EQ(board[0].size(), _row);
      }
      void test_in_range(){
        EXPECT_EQ(is_in_range("A1"),true);
        EXPECT_EQ(is_in_range("b1"),true);
        EXPECT_EQ(is_in_range("C1"),true);

        EXPECT_EQ(is_in_range("A2"),true);
        EXPECT_EQ(is_in_range("A3"),true);

        EXPECT_EQ(is_in_range("A0"),false);
        EXPECT_EQ(is_in_range("D1"),false);
      }
   }obj;

   obj.check_size(3,3);
   obj.test_in_range();

 }

 

#include "gtest/gtest.h"
#include "CountingColoredSquares.hpp"

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (helper, has_same_symbol_as_neighbors) {
    vector<vector<char>> field = {{'#',' ',' ','#'},
                                  {'#','#',' ','#'},
                                  {' ',' ','#',' '},
                                  {' ',' ','#',' '}};


    EXPECT_EQ (has_same_symbol_as_neighbors(field,0,0,'#'), true);
    EXPECT_EQ (has_same_symbol_as_neighbors(field,3,3,'#'), false);
    EXPECT_EQ (has_same_symbol_as_neighbors(field,3,0,'#'), false);
    EXPECT_EQ (has_same_symbol_as_neighbors(field,3,0,'#'), false);
    EXPECT_EQ (has_same_symbol_as_neighbors(field,3,2,'#'), true);
}

TEST (Example, Failed_Test) {
    vector<vector<char>> field = {{'#',' ',' ','#'},
                                  {'#','#',' ','#'},
                                  {' ',' ','#',' '},
                                  {' ',' ','#',' '}};

/*
    for(auto i = field.begin(); i!=field.end(); ++i){
      for(auto j = i->begin(); j!=i->end(); ++j)
        cout << *j;
      cout << endl;
    }
*/EXPECT_EQ (25.4, 111);
    cout << "Solution: " << count_symbols_horizontal_and_vertical(field, 0, 0, '#') <<endl;
    EXPECT_EQ (25.4, 111);
}

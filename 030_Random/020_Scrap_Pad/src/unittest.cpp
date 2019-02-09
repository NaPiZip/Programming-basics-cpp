#include "gtest/gtest.h"
#include "LinkedList.hpp"

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST (Test, Constructor) {
  class Tester:public LinkedList{
  public:
    Tester():LinkedList(){};
    void constructor_test(){
      EXPECT_EQ(root,nullptr);
    }
  };
  }

#include <iostream>
#include "gtest/gtest.h"
#include "LCD.hpp"

using ::testing::AtLeast;

/*
TEST (SquareRootTest, PositiveNos) {
    EXPECT_EQ (18.0, 18);
    EXPECT_EQ (25.4, 111);
}
*/
TEST (LCDTest, PositiveNos) {
    LCD oLCD;

    EXPECT_CALL(oLCD, display(15))
        .Times(AtLeast(1));

    oLCD.printNumber(15);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

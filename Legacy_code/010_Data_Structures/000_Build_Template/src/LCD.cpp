#include "LCD.hpp"
#include "gtest/gtest.h"


using ::testing::AtLeast;

void LCD::printNumber(int _number){
    this->display(_number);
    return;
}

TEST (SquareRootTest, PositiveNos) {
    EXPECT_EQ (18.0, 18);
    EXPECT_EQ (25.4, 111);
}

TEST (LCDTest, PositiveNos) {
    LCD oLCD;

    EXPECT_CALL(oLCD, display(15))
        .Times(AtLeast(1));

    oLCD.printNumber(15);
}
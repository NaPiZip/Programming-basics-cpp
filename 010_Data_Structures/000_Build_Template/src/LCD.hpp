
#ifndef _HEADER_LCD_
#define _HEADER_LCD_
#include "gmock/gmock.h"


class IDisplay {
public:
    virtual void display(int _number) = 0;
    virtual void deactivateSegment(int _segmentNo) = 0;
};

class LCD: public IDisplay {
public:
    void printNumber(int _number);

    MOCK_METHOD1(display, void(int _number));
    MOCK_METHOD1(deactivateSegment, void(int _segmentNo));
};



#endif

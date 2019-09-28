
#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include "gmock/gmock.h"

#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(expression) {std::cout << expression << std::endl;}
#else
    #define DEBUG_PRINT(expression)
#endif


#endif  /*_HEADER_WORKSPACE*/

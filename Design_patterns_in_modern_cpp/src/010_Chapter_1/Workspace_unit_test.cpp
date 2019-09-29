#include "Workspace.h"
#include "gtest/gtest.h"

namespace {

  TEST(AddTest, Positive) {
    
    EXPECT_EQ(2+3, Add(2,3));
  }
}//namespace

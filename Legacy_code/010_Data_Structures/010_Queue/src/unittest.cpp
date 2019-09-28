
#include "gtest/gtest.h"
#include "Queue.hpp"

#include <iostream>


int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (Node_test, Constructor) {
    class NodeTest: public Node
    {
      public:
        NodeTest(int val):Node(val){};
        TestCtor(int val)
        {
          EXPECT_EQ (this->data,val);
          EXPECT_EQ (this->next,nullptr);
        }
    };

    NodeTest oQueue(2);
    oQueue.TestCtor(2);
}

TEST(Que_test, Constructor)
{
  class QueueTest: public Queue
  {
  public:
      TestCtor()
      {
        EXPECT_EQ(this->head,nullptr);
        EXPECT_EQ(this->tail,nullptr);
      };
  };

  QueueTest oQueue;
  oQueue.TestCtor();
}

TEST(Que_test, add_to_queue_and_peek)
{
  int input = 5;
  Queue oQueue;
  oQueue.add(input);
  EXPECT_EQ(input,oQueue.peek());
}

TEST(Que_test, add_to_queue_and_remove_front)
{
  int input = 5;

  Queue oQueue;
  oQueue.add(input);
  EXPECT_EQ(input,oQueue.remove_front());
}

TEST(Que_test, add_to_queue_and_remove_front_twice)
{
  int input = 5;
  Queue oQueue;
  oQueue.add(input);
  EXPECT_EQ(input,oQueue.remove_front());
  EXPECT_EQ(-1,oQueue.remove_front());
}

TEST(Que_test, is_empty_call_after_defining_obj)
{
  Queue oQueue;
  EXPECT_EQ(true,oQueue.is_empty());
}

TEST(Que_test, is_empty_before_and_after_adding_one_element)
{
  int input = 4;
  Queue oQueue;
  oQueue.add(input);
  EXPECT_EQ(false,oQueue.is_empty());
  EXPECT_EQ(input,oQueue.peek());
  EXPECT_EQ(false,oQueue.is_empty());
  EXPECT_EQ(input,oQueue.remove_front());
  EXPECT_EQ(true,oQueue.is_empty());
}

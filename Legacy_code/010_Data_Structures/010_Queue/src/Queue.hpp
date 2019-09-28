
#ifndef _HEADER_QUEUE_
#define _HEADER_QUEUE_
class Node
{
  public:
      Node();
      Node(int value):data(value),next(nullptr){};

  protected:
    int data;
    Node* next;

    friend class Queue;
};


class Queue
{
  public:
    Queue():head(nullptr),tail(nullptr){};
    void add(int value);
    int peek(void);
    int remove_front(void);
    bool is_empty(void);

  protected:
    Node* head,
        * tail;
};


#endif //_HEADER_QUEUE_

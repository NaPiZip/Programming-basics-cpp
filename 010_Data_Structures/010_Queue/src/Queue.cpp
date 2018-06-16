#include "Queue.hpp"

void Queue::add(int value)
{
  if(tail == nullptr){
    tail = new Node(value);
  }  else{
    Node* newNode = new Node(value);
    tail->next = newNode;
  }
  if(head == nullptr){
    head = tail;
  }
}

int Queue::remove_front(void){
  if(head != nullptr){
    int value = head->data;
    Node* previousNode = head->next;
    delete head;
    head = previousNode;
    return value;
  }  else
    return -1;
}

int Queue::peek(){
  if(head != nullptr)
    return head->data;
  else
    return -1;
}

bool Queue::is_empty(void){
  if(head == nullptr)
    return true;
  else
    return false;
}

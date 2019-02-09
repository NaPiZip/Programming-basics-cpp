#ifndef _HEADER_LINKEDLIST_HEADER
#define _HEADER_LINKEDLIST_HEADER

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define DEBUG true
#define DEBUG_PRINT(str) if(DEBUG){cout << str << endl;}

class Node{
  public:
    Node(int value):data(value),next(nullptr), previous(nullptr){};
  protected:
    int data;
    Node* next,
        * previous;
  friend class LinkedList;
};

class LinkedList{
  public:
    LinkedList():root(nullptr){};
    void add_element(int data);
  protected:
    Node* root;

};
#endif //_HEADER_LINKEDLIST_HEADER

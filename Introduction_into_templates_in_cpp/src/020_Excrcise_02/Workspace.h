// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <exception>



class StackException : public std::exception
{
  std::string _msg;

public:
  StackException(const std::string& msg) : _msg{ msg } {}
  const char* what() const noexcept override
  {
    return _msg.c_str();
  }
};

template <typename T>
class Stack
{
protected:
  size_t _size;
  size_t _current;
  T* _data;

public:
  Stack() :_size{ 1 }, _data{ new T[1] }, _current{ 0 } {}
  ~Stack() { delete[] _data; }

  void push(const T&);
  T top();
  void pop();
};

template <typename T>
void Stack<T>::push(const T& value)
{
  if (_size == _current)
  {
    T* tmp = new T[_size * 2];
    
    for (int i = 0; i < _size; ++i)
      tmp[i] = _data[i];
    delete[] _data;
    _data = tmp;
    _size *= 2;
  }

  _data[_current] = value;
  _current++;
}

template <typename T>
T Stack<T>::top() {
  return _data[_current-1];
}

template <typename T>
void Stack<T>::pop() {
  if (_current == 0)
    throw StackException("Empty stack");
  
  _current--;
}
#endif // _HEADER_WORKSPACE

// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <string>
#include <exception>

template <typename T>
void swap(T& lhs, T& rhs)
{
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

template <typename T>
typename T::value_type sum(const T& array)
{
  typename T::value_type acc = 0;
  for (auto element : array)
  {
    acc += element;
  }
  return acc;
}


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
  Stack(size_t size) :_size{ size }, _data{ new T[size] }, _current{0} {}
  ~Stack() { delete[] _data; }
  void push(const T&);
  T top();
  void pop();
};

template <typename T>
void Stack<T>::push(const T& value)
{
  if (_size == _current)
    throw StackException("Full Stack");

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

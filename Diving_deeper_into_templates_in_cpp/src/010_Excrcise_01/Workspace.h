// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>


template <typename T, typename U>
class tuple
{
  T _first;
  U _second;

  
public:
  tuple(const T& f, const U& s) :_first{ f }, _second{ s } {}
  T first() const { return _first; }
  U second() const { return _second; }

  
private:
  friend bool operator==(const tuple<T, U>& lhs, const tuple<T, U>& rhs)
  {
    return (lhs.first() == rhs.first() && lhs.second() == rhs.second());
  }
};


class MyArrayException : public std::exception
{
  std::string _msg;

public:
  MyArrayException(const std::string& s) : _msg{ s } {}
  const char* what() const override {
    return  _msg.c_str();
  }

};

template <typename T, typename U>
class MyArray
{
  std::vector<tuple<T, U>> _data;

public:
  void add( tuple<T, U>& t)
  {
    if (_data.end() == std::find(_data.begin(), _data.end(), t))
      _data.push_back(t);
    else
    {
      throw MyArrayException("Already in MyArray");
    }
  }

  U get(const T& t) {  
    auto match = std::find_if(_data.begin(), _data.end(), [&t](const tuple<T, U>& tup) { return tup.first() == t; });
    if (match != _data.end())
      return match->second();
    else
    {
      throw MyArrayException("Key not found");
    }
  }

  U getOrElse(const T& t, const U& value)
  {
    try {
      return get(t);
    }
    catch (const MyArrayException ) {
      return value;
    }
  }

  U operator[](const T& t)
  {
    return get(t);
  }
};


// std out logger policy or null
//timer policy

class LoggingPolicy
{
public:
  virtual void info(const std::string&) = 0;
  virtual void warning(const std::string&) = 0;
  virtual void error(const std::string&) = 0;
};

class StdOut : public LoggingPolicy
{
public:
  virtual void info(const std::string& s) override { std::cout << "INFO: " << s << std::endl; };
  virtual void warning(const std::string& s) override { std::cout << "WARNING: " << s << std::endl; };
  virtual void error(const std::string& s) override { std::cout << "ERROR: " << s << std::endl; };

};

class NoOut : public LoggingPolicy
{
public:
  virtual void info(const std::string& s) override { };
  virtual void warning(const std::string& s) override { };
  virtual void error(const std::string& s) override { };
};

template <typename Policy>
class Logger : public Policy
{
public:
  void doSomething(const std::string& s)
  {
    this->info(s);
  }
};

#endif // _HEADER_WORKSPACE

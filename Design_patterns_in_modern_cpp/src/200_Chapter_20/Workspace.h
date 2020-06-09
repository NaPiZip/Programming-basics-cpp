// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <string>
#include <vector>
#include "boost/signals2/signal.hpp"

/*
struct PersonListener {
  virtual void person_changed(Person& p, const std::string& property_name, any new_value) = 0;
};*/

struct Person;

template <typename T>
struct Observer {
  virtual void field_changed(T& source, const std::string& field_name) = 0;
};

struct ConsolePersonObserver : Observer<Person> {
  void field_changed(Person& source, const std::string& field_name) override;
};

template <typename T>
struct Observable {
  void notify(T& source, const std::string& name) {
    for (auto obs : observers_)
      obs->field_changed(source, name);
  }
  void subscribe(Observer<T>* f) {
    observers_.push_back(f);
  }
  void unsubscribe(Observer<T>* f) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), f), observers_.end());
  }

private:
  std::vector<Observer<T>*> observers_;
};

struct Person : Observable<Person>{
private:
  int age_;

public:
  Person(int age) : age_{ age } {}
  int get_age() const;
  void set_age(int value);
  bool get_can_vote() const;
};

template <typename T> 
struct ObservableWithSignal {
  boost::signals2::signal<void(T&, const std::string&)> property_changed_;
};

struct PersonWithSignal : ObservableWithSignal<PersonWithSignal> {
private:
  int age_;

public:
  PersonWithSignal(int age) : age_{ age } {}
  void set_age(int age);
};

#endif // _HEADER_WORKSPACE

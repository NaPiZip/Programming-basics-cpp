// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <iostream>
#include <memory>
#include <vector>

class Memento;

class BankAccount {
  int balance_ = 0;

public:
  explicit BankAccount(int balance) : balance_{ balance } {}
  Memento deposit(int amount);
  void resore(const Memento& m);

  private:
  friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj);
};

class Memento {
  int balance_;
public:
  Memento(int balance) : balance_{ balance } {}
  friend class BankAccount;
  friend class BankAccount2;
};

class BankAccount2 {
  int balance_ = 0;
  std::vector<std::shared_ptr<Memento>> changes_;
  int current_;

public:
  explicit BankAccount2(int balance) : balance_{ balance } {
    changes_.emplace_back(std::make_shared<Memento>(balance));
    current_ = 0;
  }
  std::shared_ptr<Memento> deposit(int amount);
  void restore(const std::shared_ptr<Memento>& m);
  std::shared_ptr<Memento> undo();
  std::shared_ptr<Memento> redo();

   private:
  friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj);
};
#endif // _HEADER_WORKSPACE

// Copyright 2019, Nawin

#include "Workspace.h"

Memento BankAccount::deposit(int amount) {
  balance_ += amount;
  return { balance_ };
}

void BankAccount::resore(const Memento& m) {
  balance_ = m.balance_;
}

std::ostream& operator<<(std::ostream& os, const BankAccount& obj) {
  return os << "The balance is: " << obj.balance_ << "\n";
}

std::shared_ptr<Memento> BankAccount2::deposit(int amount) {
  balance_ += amount;
  auto m = std::make_shared<Memento>(balance_);
  changes_.push_back(m);
  current_++;
  return m;
}

void BankAccount2::restore(const std::shared_ptr<Memento>& m) {
  if (m) {
    balance_ = m->balance_;
    changes_.push_back(m);
    current_ = changes_.size() - 1;
  }
}

std::shared_ptr<Memento> BankAccount2::undo() {
  if (current_ > 0) {
    --current_;
    auto m = changes_[current_];
    balance_ = m->balance_;
    return m;
  }
  return {};
}

std::shared_ptr<Memento> BankAccount2::redo() {
  if (current_ + 1 < changes_.size()) {
    ++current_;
    auto m = changes_[current_];
    balance_ = m->balance_;
    return m;
  }
  return {};
 }

std::ostream& operator<<(std::ostream& os, const BankAccount2& obj) {
   return os << "The balance is: " << obj.balance_ << "\n";
 }

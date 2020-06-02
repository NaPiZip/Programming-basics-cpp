// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>

void BankAccount::deposit(int amount) {
  balance_ += amount;
  std::cout << "deposited " << amount << " , balance is now " << balance_ << '\n';
}

bool BankAccount::withdraw(int amount) {

  if (balance_ - amount >= overdraft_limit_) 
  {
    balance_ -= amount;
    std::cout << "witdrew " << amount << " , balance is now " << balance_ << '\n';
    return true;
  }
  return false;
}

void BankAccountCommand::call() {
  switch (action_) {
  case BankAccountCommand::deposit:
    account_.deposit(amount_);
    break;
  case BankAccountCommand::withdraw:
    withdrawal_succeeded_ = account_.withdraw(amount_);
    break;
  default:
    break;
  }
}

void BankAccountCommand::undo() {
  switch (action_) {
  case BankAccountCommand::deposit:
    account_.withdraw(amount_);
    break;
  case BankAccountCommand::withdraw:
    if (withdrawal_succeeded_)
      account_.deposit(amount_);
    break;
  default:
    break;
  }
}

void CompositeBankAccountCommand::call() {
  for (auto& cmd : *this)
    cmd.call();
}

void CompositeBankAccountCommand::undo() {
  for (auto it = rbegin(); it != rend(); ++it)
    it->undo();
}

void Creature::process_command(const CreatureCommand& cc) {
  int* ability;
  switch (cc.ability_) {
  case CreatureAbility::strenght:
    ability = &strength_;
    break;
  case CreatureAbility::agility:
    ability = &agility_;
    break;
  default:
    break;
  }
  switch (cc.action_) {
  case CreatureCommand::set:
    *ability = cc.amount_;
    break;
  case CreatureCommand::increaseBy:
    *ability += cc.amount_;
    break;
  case CreatureCommand::decreaseBy:
    *ability -= cc.amount_;
  default:
    break;
  }
}

int Creature::process_query(CreatureQuery& q) const {
  switch (q.ability_) {
  case CreatureAbility::agility:
    q.value_ = agility_;
    return agility_;
  case CreatureAbility::strenght:
    q.value_ = strength_;
    return strength_;
  default:
    return 0;
    break;
  }
}

void Creature::set_strength(int strength) {
  process_command(CreatureCommand{ CreatureCommand::set, CreatureAbility::strenght, strength });
}
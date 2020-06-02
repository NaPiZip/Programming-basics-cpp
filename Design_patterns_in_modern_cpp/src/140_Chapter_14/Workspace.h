// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

#include <initializer_list>
#include <vector>


struct BankAccount {
  int balance_ = 0;
  int overdraft_limit_ = -500;

  void deposit(int amount);
  bool withdraw(int amount);
};


struct Command {
  virtual void call() = 0;
  virtual void undo() = 0;
};


struct BankAccountCommand : Command {
  BankAccount& account_;
  enum Action { deposit,
    withdraw } action_;
  int amount_;
  bool withdrawal_succeeded_{ false };

  BankAccountCommand(BankAccount& account, const Action action, const int amount) : account_{ account }, action_{ action }, amount_{ amount } {  }
  void call() override;
  void undo() override;
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command {
  CompositeBankAccountCommand(const std::initializer_list<value_type>& items) : std::vector<BankAccountCommand>(items) {}
  void call() override;
  void undo() override;
};

struct MoneyTransferCommand : CompositeBankAccountCommand {
  MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount) : CompositeBankAccountCommand{
                                                                           BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                                                                           BankAccountCommand{to, BankAccountCommand::deposit, amount}} {}
};

enum class CreatureAbility { strenght,
  agility };

struct CreatureCommand {
  enum Action { set,
    increaseBy,
    decreaseBy } action_;
  CreatureAbility ability_;
  int amount_;
};
struct CreatureQuery {
  CreatureAbility ability_;
  int value_;
};

class Creature {
  int strength_, agility_;

public:
  Creature(int strength, int agility) : strength_{ strength }, agility_{ agility } {}
  void process_command(const CreatureCommand& cc);
  int process_query(CreatureQuery& q) const;
  void set_strength(int strength);
};

#endif // _HEADER_WORKSPACE

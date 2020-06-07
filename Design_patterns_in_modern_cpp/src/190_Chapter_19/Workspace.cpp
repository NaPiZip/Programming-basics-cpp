// Copyright 2019, Nawin

#include "Workspace.h"
#include <iostream>


void ConsoleLogger::info(const std::string& s) {
  std::cout << "INFO: " << s << "\n";
}

void ConsoleLogger::warn(const std::string& s) {
  std::cout << "WARN: " << s << "\n";
}

void BankAccount::deposit(int amount) {
  balance_ += amount;
  log_->info("Deposited $" + std::to_string(amount) + " to " + name_ + ", balance is now $" + std::to_string(balance_));
}

void OptionalLogger::info(const std::string& s) {
  if (impl_)
    impl_->info(s);
}
std::shared_ptr<Logger> OptionalLogger::no_logging_ {};
// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
#include <memory>
#include <string>

struct Logger {
  virtual ~Logger() = default;
  virtual void info(const std::string& s) = 0;
  virtual void warn(const std::string& s) = 0;
};

struct ConsoleLogger : Logger {
  void info(const std::string& s) override;
  void warn(const std::string& s) override;
};

struct NullLogger : Logger {
  void info(const std::string& s) override {}
  void warn(const std::string& s) override {}
};

struct OptionalLogger : Logger {
  std::shared_ptr<Logger> impl_;
  static std::shared_ptr<Logger> no_logging_;
  OptionalLogger(const std::shared_ptr<Logger>& logger) : impl_{ logger } {}
  virtual void info(const std::string& s) override;
};

struct BankAccount {
  std::shared_ptr<Logger> log_;
  std::shared_ptr<OptionalLogger> logger_;
  std::string name_;
  int balance_ = 0;

  BankAccount(const std::shared_ptr<Logger>& logger, std::string& name, int balance) : log_{ logger }, name_{ name }, balance_{ balance } {}
  void deposit(int amount);
};


#endif // _HEADER_WORKSPACE

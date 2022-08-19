#pragma once
#include <string>

class BankDeposit {
protected:
  long open_date;
  long termination_date;
  double rate;
  double amount;

public:
  BankDeposit(long _open_date, long _terminate_date, double _rate,
              double _amount);
  virtual double calculate_income(long to) = 0;
  virtual double calculate_income() = 0;

  virtual std::string print_class_name() = 0;
};

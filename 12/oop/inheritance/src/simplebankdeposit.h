#pragma once
#include "bankdeposit.h"

class SimpleBankDeposit : public BankDeposit {
public:
  SimpleBankDeposit(long _open_date, long _terminate_date, double _rate,
                    double _amount);
  std::string print_class_name() override;
  double calculate_income(long to) override;
  double calculate_income() override;
};

#pragma once
#include "complexbankdeposit.h"

class VIPBankDeposit : public ComplexBankDeposit {
public:
  VIPBankDeposit(long _open_date, long _terminate_date, double _rate,
                 double _amount);
  void add_money(double);
  std::string print_class_name() override;
};

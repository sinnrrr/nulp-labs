#include "bankdeposit.h"

BankDeposit::BankDeposit(long _open_date, long _terminate_date, double _rate,
                         double _amount) {
  open_date = _open_date;
  termination_date = _terminate_date;
  rate = _rate;
  amount = _amount;
}

std::string BankDeposit::print_class_name() { return "BankDeposit"; }

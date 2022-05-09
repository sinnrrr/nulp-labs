#include "simplebankdeposit.h"

SimpleBankDeposit::SimpleBankDeposit(long _open_date, long _terminate_date,
                                     double _rate, double _amount)
    : BankDeposit(_open_date, _terminate_date, _rate, _amount) {}

double SimpleBankDeposit::calculate_income(long to) {
  auto month_count = (to - this->open_date) / (60. * 60 * 24 * 30);
  return this->amount * rate * month_count;
}

double SimpleBankDeposit::calculate_income() {
  return this->calculate_income(this->termination_date);
}

std::string SimpleBankDeposit::print_class_name() {
  return "SimpleBankDeposit";
}

#include "complexbankdeposit.h"

ComplexBankDeposit::ComplexBankDeposit(long _open_date, long _terminate_date,
                                       double _rate, double _amount)
    : BankDeposit(_open_date, _terminate_date, _rate, _amount) {}

double ComplexBankDeposit::calculate_income(long to) {
  auto month_count = (to - this->open_date) / (60. * 60 * 24 * 30);
  auto progressive_amount = this->amount;
  for (auto i = 0; i < month_count; i++) {
    progressive_amount += progressive_amount * rate;
  }
  return progressive_amount - this->amount;
}

double ComplexBankDeposit::calculate_income() {
  return this->calculate_income(this->termination_date);
}

std::string ComplexBankDeposit::print_class_name() {
  return "ComplexBankDeposit";
}

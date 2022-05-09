#include "vipbankdeposit.h"

VIPBankDeposit::VIPBankDeposit(long _open_date, long _terminate_date,
                               double _rate, double _amount)
    : ComplexBankDeposit(_open_date, _terminate_date, _rate, _amount) {}

void VIPBankDeposit::add_money(double money) {
  this->amount += money;
  this->rate = std::min(.02, this->rate + money / 1000000);
}

std::string VIPBankDeposit::print_class_name() { return "VIPBankDeposit"; }

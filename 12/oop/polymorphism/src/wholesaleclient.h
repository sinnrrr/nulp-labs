#pragma once
#include <string>

class WholesaleClient {
protected:
  std::string name;
  unsigned short age;
  unsigned long balance;

public:
  BankDeposit(long _open_date, long _terminate_date, double _rate,
              double _amount);
  virtual double calculate_income(long to) = 0;
  virtual double calculate_income() = 0;

  virtual std::string print_class_name() = 0;
};

class RegularWholesaleClient : public WholesaleClient {
public:
  SimpleBankDeposit(long _open_date, long _terminate_date, double _rate,
                    double _amount);
  std::string print_class_name() override;
  double calculate_income(long to) override;
  double calculate_income() override;
};

class VipWholesaleClient : public WholesaleClient {
public:
  ComplexBankDeposit(long _open_date, long _terminate_date, double _rate,
                     double _amount);
  std::string print_class_name() override;
  double calculate_income(long to) override;
  double calculate_income() override;
};

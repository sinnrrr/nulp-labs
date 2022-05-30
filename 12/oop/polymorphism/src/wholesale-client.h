#pragma once
#include <iostream>
#include <string>

using std::string;

// Wholesale thing entity
struct WholesaleThing {
  string id;
  string name;
  double price;
};

template <typename BuyEntity> struct CanDoPurchases {
  virtual void buy(BuyEntity thing) = 0;
};

// Wholesale client general class, as base for other classes
class WholesaleClient : CanDoPurchases<WholesaleThing> {
protected:
  string name;
  double balance;
  double discount_percent = 0;
  bool notifiable = false;

public:
  WholesaleClient(string name, double balance = 0) {
    this->name = name;
    this->balance = balance;
  };

  virtual string getClassName() { return "WholesaleClient"; };

  double getPriceWithDiscount(double itemPrice) {
    return itemPrice - (itemPrice * this->discount_percent);
  }

  void buy(WholesaleThing thing) override {
    const auto priceWithDiscount = this->getPriceWithDiscount(thing.price);

    if (this->balance < priceWithDiscount) {
      throw std::invalid_argument("Balance can't be lower than the price");
    }

    this->balance -= priceWithDiscount;

    if (this->notifiable) {
      std::cout << "The item with ID " << thing.id
                << " was successfully purchased";
    }

    return;
  }
};

class RegularWholesaleClient : public WholesaleClient {
public:
  RegularWholesaleClient(string name, double balance = 0)
      : WholesaleClient(name, balance) {
    this->discount_percent = 0;
    this->notifiable = false;
  };

  string getClassName() override { return "RegularWholesaleClient"; };
};

class ComplexWholesaleClient : public WholesaleClient {

public:
  ComplexWholesaleClient(string name, double balance = 0)
      : WholesaleClient(name, balance) {
    this->discount_percent = 0.05;
    this->notifiable = true;
  }

  string getClassName() override { return "ComplexWholesaleClient"; }
};

class VipWholesaleClient : public ComplexWholesaleClient {
public:
  VipWholesaleClient(string name, double balance = 0)
      : ComplexWholesaleClient(name, balance) {
    this->discount_percent = 0.1;
    this->notifiable = true;
  }

  string getClassName() override { return "VipWholesaleClient"; }
};

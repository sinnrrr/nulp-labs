#ifndef FRACTION_H
#define FRACTION_H
#include <QLineEdit>
#include <QRegularExpression>
#include <string>
using std::string;

class Fraction {
  int nominator;
  int denominator;

public:
  Fraction() throw() {
    nominator = 1;
    denominator = 1;
  }
  Fraction(int n, int d) {
    nominator = n;
    denominator = d;
  }
  void Input(QLineEdit *nomin, QLineEdit *denom) noexcept(false) {
    if (nomin == nullptr || denom == nullptr)
      throw string("Error with QLineEdit* pointers!");
    if (nomin->text().contains(QRegularExpression("[^0-9.,]")))
      throw string("Nominator cannot contain non-number symbols");
    if (denom->text().contains(QRegularExpression("[^0-9.,]")))
      throw string("Denominator cannot contain non-number symbols");
    if (nomin->text().contains(QRegularExpression("[,.]")))
      throw 0.1;
    if (denom->text().contains(QRegularExpression("[,.]")))
      throw 0.1;
    if (nomin->text().toLongLong() > INT_MAX ||
        nomin->text().toLongLong() < INT_MIN)
      throw QString("int memory overflow in nominator");
    if (denom->text().toLongLong() > INT_MAX ||
        denom->text().toLongLong() < INT_MIN)
      throw QString("int memory overflow in denominator");
    nominator = nomin->text().toInt();
    denominator = denom->text().toInt();
    if (denominator == 0)
      throw 0;
  }
  void Print(QLineEdit *nomin, QLineEdit *denom) noexcept(false) {
    if (nomin == nullptr || denom == nullptr)
      throw string("Error with QLineEdit* pointers!");
    nomin->setText(QString::number(nominator));
    denom->setText(QString::number(denominator));
  }
  Fraction operator+(Fraction &f) throw() {
    return Fraction(nominator * f.denominator + denominator * f.nominator,
                    denominator * f.denominator);
  }
  Fraction operator-(Fraction &f) throw() {
    return Fraction(nominator * f.denominator - denominator * f.nominator,
                    denominator * f.denominator);
  }
  Fraction operator*(Fraction &f) throw() {
    return Fraction(nominator * f.nominator, denominator * f.denominator);
  }
  Fraction operator/(Fraction &f) throw() {
    return Fraction(nominator * f.denominator, denominator * f.nominator);
  }
  Fraction Flip() noexcept(false) {
    if (nominator == 0)
      throw 0;
    return Fraction(denominator, nominator);
  }
};

#endif // FRACTION_H

#pragma once

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);

private slots:
  void on_plus_clicked();
  void on_minus_clicked();
  void on_divide_clicked();
  void on_product_clicked();
  void on_flip_clicked();

private:
  QLabel *operation;

  QLineEdit *nomin1;
  QLineEdit *nomin2;
  QLineEdit *nomin3;
  QLineEdit *denom1;
  QLineEdit *denom2;
  QLineEdit *denom3;

  QPushButton *plus;
  QPushButton *minus;
  QPushButton *divide;
  QPushButton *product;
  QPushButton *flip;
};

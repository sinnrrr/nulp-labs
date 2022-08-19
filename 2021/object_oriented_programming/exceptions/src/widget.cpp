#include "widget.h"
#include "fraction.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

void Widget::on_plus_clicked() {
  try {
    Fraction f1;
    f1.Input(this->nomin1, this->denom1);
    Fraction f2;
    f2.Input(this->nomin2, this->denom2);
    this->operation->setText("+");
    (f1 + f2).Print(this->nomin3, this->denom3);
  } catch (string ex) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(ex));
    msgBox.exec();
  } catch (int ex) {
    QMessageBox msgBox;
    msgBox.setText("Cannot divide by zero");
    msgBox.exec();
  } catch (double ex) {
    QMessageBox msgBox;
    msgBox.setText("Non-integer numbers are not allowed");
    msgBox.exec();
  } catch (QString ex) {
    QMessageBox msgBox;
    msgBox.setText(ex);
    msgBox.exec();
  } catch (...) {
  }
}

void Widget::on_minus_clicked() {
  try {
    Fraction f1;
    f1.Input(this->nomin1, this->denom1);
    Fraction f2;
    f2.Input(this->nomin2, this->denom2);
    this->operation->setText("-");
    (f1 - f2).Print(this->nomin3, this->denom3);
  } catch (string ex) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(ex));
    msgBox.exec();
  } catch (int ex) {
    QMessageBox msgBox;
    msgBox.setText("Cannot divide by zero");
    msgBox.exec();
  } catch (double ex) {
    QMessageBox msgBox;
    msgBox.setText("Non-integer numbers are not allowed");
    msgBox.exec();
  } catch (QString ex) {
    QMessageBox msgBox;
    msgBox.setText(ex);
    msgBox.exec();
  } catch (...) {
  }
}

void Widget::on_divide_clicked() {
  try {
    Fraction f1;
    f1.Input(this->nomin1, this->denom1);
    Fraction f2;
    f2.Input(this->nomin2, this->denom2);
    this->operation->setText("/");
    (f1 / f2).Print(this->nomin3, this->denom3);
  } catch (string ex) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(ex));
    msgBox.exec();
  } catch (int ex) {
    QMessageBox msgBox;
    msgBox.setText("Cannot divide by zero");
    msgBox.exec();
  } catch (double ex) {
    QMessageBox msgBox;
    msgBox.setText("Non-integer numbers are not allowed");
    msgBox.exec();
  } catch (QString ex) {
    QMessageBox msgBox;
    msgBox.setText(ex);
    msgBox.exec();
  } catch (...) {
  }
}

void Widget::on_product_clicked() {
  try {
    Fraction f1;
    f1.Input(this->nomin1, this->denom1);
    Fraction f2;
    f2.Input(this->nomin2, this->denom2);
    this->operation->setText("*");
    (f1 * f2).Print(this->nomin3, this->denom3);
  } catch (string ex) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(ex));
    msgBox.exec();
  } catch (int ex) {
    QMessageBox msgBox;
    msgBox.setText("Cannot divide by zero");
    msgBox.exec();
  } catch (double ex) {
    QMessageBox msgBox;
    msgBox.setText("Non-integer numbers are not allowed");
    msgBox.exec();
  } catch (QString ex) {
    QMessageBox msgBox;
    msgBox.setText(ex);
    msgBox.exec();
  } catch (...) {
  }
}

void Widget::on_flip_clicked() {
  try {
    Fraction f1;
    f1.Input(this->nomin1, this->denom1);
    this->operation->setText("");
    this->nomin2->clear();
    this->denom2->clear();
    (f1.Flip()).Print(this->nomin3, this->denom3);
  } catch (string ex) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(ex));
    msgBox.exec();
  } catch (int ex) {
    QMessageBox msgBox;
    msgBox.setText("Cannot divide by zero");
    msgBox.exec();
  } catch (double ex) {
    QMessageBox msgBox;
    msgBox.setText("Non-integer numbers are not allowed");
    msgBox.exec();
  } catch (QString ex) {
    QMessageBox msgBox;
    msgBox.setText(ex);
    msgBox.exec();
  } catch (...) {
  }
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->nomin1 = new QLineEdit();
  this->nomin2 = new QLineEdit();
  this->nomin3 = new QLineEdit();
  this->denom1 = new QLineEdit();
  this->denom2 = new QLineEdit();
  this->denom3 = new QLineEdit();

  this->plus = new QPushButton("+");
  this->minus = new QPushButton("-");
  this->product = new QPushButton("*");
  this->divide = new QPushButton("/");
  this->flip = new QPushButton("flip");

  this->operation = new QLabel();

  main_layout->addWidget(this->nomin1, 0, 0);
  main_layout->addWidget(this->denom1, 1, 0);
  main_layout->addWidget(this->operation, 0, 1);
  main_layout->addWidget(this->nomin2, 0, 2);
  main_layout->addWidget(this->denom2, 1, 2);
  main_layout->addWidget(new QLabel("="), 0, 3);
  main_layout->addWidget(this->nomin3, 0, 4);
  main_layout->addWidget(this->denom3, 1, 4);

  main_layout->addWidget(this->plus, 2, 0);
  main_layout->addWidget(this->minus, 2, 1);
  main_layout->addWidget(this->product, 2, 2);
  main_layout->addWidget(this->divide, 2, 3);
  main_layout->addWidget(this->flip, 2, 4);

  connect(this->plus, &QPushButton::released, this, &Widget::on_plus_clicked);
  connect(this->minus, &QPushButton::released, this, &Widget::on_minus_clicked);
  connect(this->product, &QPushButton::released, this,
          &Widget::on_product_clicked);
  connect(this->divide, &QPushButton::released, this,
          &Widget::on_divide_clicked);
  connect(this->flip, &QPushButton::released, this, &Widget::on_flip_clicked);

  setLayout(main_layout);
}

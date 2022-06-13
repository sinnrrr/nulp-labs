#include "widget.h"
#include "custom-set.h"
#include "custom-string.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;

void Widget::onValueChange() {
  this->leftSetList->clear();
  this->rightSetList->clear();
  this->intersectionSetList->clear();

  int i = 0;

  i = 0;
  for (auto el : *this->leftSet) {
    this->leftSetList->insertItem(i++, el);
  }

  i = 0;
  for (auto el : *this->rightSet) {
    this->rightSetList->insertItem(i++, el);
  }

  i = 0;
  for (auto el : this->leftSet->intersection(this->rightSet)) {
    this->intersectionSetList->insertItem(i++, el);
  }
}

void Widget::onClear() {
  this->leftSet->erase();
  this->rightSet->erase();

  emit valueChanged();
}

void Widget::onOutput() {
  vector<SetElementType> a;
  vector<SetElementType> b;

  int int1 = 1;
  int int2 = 2;
  int int3 = 3;

  a.push_back(int1);
  a.push_back(int2);
  a.push_back(int3);

  b.push_back(int1);
  b.push_back(int2);

  this->leftSet = new CustomSet<SetElementType>(a);
  this->rightSet = new CustomSet<SetElementType>(b);

  emit valueChanged();
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *mainLayout = new QGridLayout;

  this->outputButton = new QPushButton("Print output");
  this->clearButton = new QPushButton("Clear");

  this->leftSetList = new QListWidget;
  this->rightSetList = new QListWidget;
  this->intersectionSetList = new QListWidget;

  mainLayout->addWidget(this->leftSetList, 0, 0, 2, 1);
  mainLayout->addWidget(this->rightSetList, 0, 1, 2, 1);
  mainLayout->addWidget(this->intersectionSetList, 2, 0, 1, 2);
  mainLayout->addWidget(this->outputButton, 3, 0);
  mainLayout->addWidget(this->clearButton, 3, 1);

  connect(this->outputButton, &QPushButton::released, this, &Widget::onOutput);
  connect(this->clearButton, &QPushButton::released, this, &Widget::onClear);
  connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}

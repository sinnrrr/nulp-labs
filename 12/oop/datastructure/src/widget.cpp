#include "widget.h"

#include <QGridLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;

  this->dq = new CustomDeque;

  this->listWidget = new QListWidget;
  this->tableWidget = new QTableWidget;

  this->addListItemButton = new QPushButton("Add list item");
  this->addTableItemButton = new QPushButton("Add table item");
  this->clearQueueButton = new QPushButton("Clear queue");

  this->minValueInput = new QLineEdit;
  this->maxValueInput = new QLineEdit;
  this->averageValueInput = new QLineEdit;

  mainLayout->addWidget(this->listWidget, 0, 0);
  mainLayout->addWidget(this->addListItemButton, 1, 0);

  mainLayout->addWidget(this->tableWidget, 0, 1);
  mainLayout->addWidget(this->addTableItemButton, 1, 1);
  mainLayout->addWidget(this->clearQueueButton, 2, 0, 1, 2);

  mainLayout->addWidget(new QLabel("Biggest value:"), 3, 0);
  mainLayout->addWidget(this->maxValueInput, 3, 1);

  mainLayout->addWidget(new QLabel("Minimum value:"), 4, 0);
  mainLayout->addWidget(this->minValueInput, 4, 1);

  mainLayout->addWidget(new QLabel("Average value:"), 5, 0);
  mainLayout->addWidget(this->averageValueInput, 5, 1);

  connect(this->addListItemButton, &QPushButton::released, this,
          &Widget::onAddListItem);

  connect(this->addTableItemButton, &QPushButton::released, this,
          &Widget::onAddTableItem);

  connect(this->clearQueueButton, &QPushButton::released, this,
          &Widget::onQueueClear);

  connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}

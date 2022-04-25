#pragma once

#include "customdeque.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);

private slots:
  void onAddListItem();
  void onAddTableItem();
  void onQueueClear();
  void onValueChange(CustomDeque *dq);

signals:
  void valueChanged(CustomDeque *dq);

private:
  CustomDeque *dq;

  QListWidget *listWidget;
  QTableWidget *tableWidget;

  QPushButton *addListItemButton;
  QPushButton *addTableItemButton;

  QPushButton *clearQueueButton;

  QLineEdit *minValueInput;
  QLineEdit *maxValueInput;
  QLineEdit *averageValueInput;
};

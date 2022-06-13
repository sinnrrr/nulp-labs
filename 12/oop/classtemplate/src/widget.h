#pragma once

#include "custom-set.h"
#include "custom-string.h"
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

signals:
  void valueChanged();

public:
  Widget(QWidget *parent = nullptr);

private slots:
  void onClear();
  void onOutput();
  void onValueChange();

private:
  CustomSet<SetElementType> *leftSet;
  CustomSet<SetElementType> *rightSet;

  QPushButton *outputButton;
  QPushButton *clearButton;

  QListWidget *leftSetList;
  QListWidget *rightSetList;
  QListWidget *intersectionSetList;
};

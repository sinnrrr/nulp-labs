#pragma once

#include "triangle.h"

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
  void onInputConfirm();
  void onInputIncreaseBy();
  void onInputIncreaseTimes();
  void onValueChange(Triangle *triangle);

signals:
  void valueChanged(Triangle *triangle);

private:
  QLineEdit *side_a;
  QLineEdit *side_b;
  QLineEdit *side_c;
  QPushButton *confirmInput;

  QLineEdit *increaseSidesBy;
  QLineEdit *increaseSidesTimes;

  QPushButton *confirmIncreaseBy;
  QPushButton *confirmIncreaseTimes;

  QLineEdit *area;
  QLineEdit *perimeter;
  QLineEdit *isRectangular;
  QTextEdit *angles;
  QTextEdit *heights;

  Triangle *triangle;
};

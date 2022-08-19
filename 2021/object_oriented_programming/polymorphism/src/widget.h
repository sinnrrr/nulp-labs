#pragma once

#include "wholesale-client.h"
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);

private slots:
  void on_output();

private:
  std::vector<WholesaleClient *> operated_classes;

  QPushButton *output_btn;

  QTextEdit *class_names_output;
  QTextEdit *results_output;
};

#pragma once

#include <QFile>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QWidget>
#include <map>

class Widget : public QWidget {
  Q_OBJECT

  using OperatedType = const char *;

public:
  Widget(QWidget *parent = nullptr);
  void print_array();

  std::map<OperatedType, bool> map;
  std::vector<OperatedType> vector;
  std::vector<OperatedType> vector2;
private slots:
  void on_start();

private:
  QPushButton *start_btn;
  QTextEdit *output_1;
  QTextEdit *output_2;
  QTextEdit *output_3;
  QTextEdit *output_4;
};

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = nullptr); // Constructor
  ~MainWidget();                                  // Destructor

private:
  QPushButton *button_;
  QTextBrowser *textBrowser_;
};

#endif

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDebug>
#include <QProcess>
#include <QWidget>

class QPushButton;
class QTextBrowser;

class MainWidget : public QWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = nullptr); // Constructor
  ~MainWidget();                                  // Destructor

private slots:
  void onButtonReleased();       // Handler for button presses
  void onCaptureProcessOutput(); // Handler for Process output

private:
  QPushButton *button_;
  QTextBrowser *textBrowser_;
  QProcess process_;
};

#endif // MAINWIDGET_H

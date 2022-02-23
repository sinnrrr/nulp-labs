#include "mainwidget.h"

#include <QtWidgets>

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  button_ = new QPushButton("Push Me!");
  textBrowser_ = new QTextBrowser();

  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->addWidget(button_, 0, 0);
  mainLayout->addWidget(textBrowser_, 1, 0);

  setLayout(mainLayout);
  setWindowTitle(tr("Connecting buttons to processes.."));

  connect(button_, &QPushButton::released, this, &MainWidget::onButtonReleased);
  connect(&process_, &QProcess::readyReadStandardOutput, this,
          &MainWidget::onCaptureProcessOutput);
}

// Destructor
MainWidget::~MainWidget() {
  delete button_;
  delete textBrowser_;
}

void MainWidget::onButtonReleased() {
  textBrowser_->clear();
  textBrowser_->append("Running command:");

  process_.setCurrentWriteChannel(QProcess::StandardOutput);
  process_.start("ls -alh $HOME/Documents");
}

void MainWidget::onCaptureProcessOutput() {
  QProcess *process = qobject_cast<QProcess *>(sender());

  textBrowser_->append("Listen");

  if (process) {
    textBrowser_->append(tr("Gotcha"));
    textBrowser_->append(process->readAllStandardOutput());
  }
}

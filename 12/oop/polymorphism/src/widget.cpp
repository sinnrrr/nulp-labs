#include "widget.h"
#include "wholesale-client.h"

#include <QFile>
#include <QGridLayout>
#include <QTextStream>
#include <iostream>
#include <vector>

void Widget::on_output() {
  const string clientName = "Clementh";
  const auto balanceForEveryone = 100;

  const WholesaleThing thing = {"123",    // id
                                "Shovel", // name
                                15};

  this->operated_classes.push_back(
      new RegularWholesaleClient(clientName, balanceForEveryone));
  this->operated_classes.push_back(
      new ComplexWholesaleClient(clientName, balanceForEveryone));
  this->operated_classes.push_back(
      new VipWholesaleClient(clientName, balanceForEveryone));

  std::cout << (new ComplexWholesaleClient(clientName, balanceForEveryone))
                   ->getClassName()
            << '\n'
            << this->operated_classes[1]->getClassName();

  this->class_names_output->setMarkdown(
      QString("### WholesaleClient clild classes:\n\n"
              "* %1\n"
              "* %2\n"
              "* %3")
          .arg(
              QString::fromStdString(this->operated_classes[0]->getClassName()))
          .arg(
              QString::fromStdString(this->operated_classes[1]->getClassName()))
          .arg(QString::fromStdString(
              this->operated_classes[2]->getClassName())));

  auto output_string =
      QString("### Parameters\n"
              "`balance = %4, wholesale thing price = %5`:\n"
              "\n"
              "### Result price\n"
              "* Regular: %1\n"
              "* Complex: %2\n"
              "* VIP: %3")
          .arg(QString::number(
              this->operated_classes[0]->getPriceWithDiscount(thing.price)))
          .arg(QString::number(
              this->operated_classes[1]->getPriceWithDiscount(thing.price)))
          .arg(QString::number(
              this->operated_classes[2]->getPriceWithDiscount(thing.price)))
          .arg(QString::number(balanceForEveryone))
          .arg(QString::number(thing.price));

  QFile file("results.md");
  if (file.open(QIODevice::Append)) {
    QTextStream stream(&file);
    stream << output_string << Qt::endl << Qt::endl;
    file.close();
  }
  this->results_output->setMarkdown(output_string);
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->output_btn = new QPushButton("Print output");

  this->class_names_output = new QTextEdit;
  this->class_names_output->setReadOnly(true);

  this->results_output = new QTextEdit;
  this->results_output->setReadOnly(true);

  main_layout->addWidget(this->class_names_output, 0, 0);
  main_layout->addWidget(this->results_output, 0, 1);
  main_layout->addWidget(this->output_btn, 1, 0, 1, 2);

  connect(this->output_btn, &QPushButton::released, this, &Widget::on_output);

  setLayout(main_layout);
}

#include "widget.h"
#include "triangle.h"
#include "triangleangles.h"
#include "trianglesides.h"

#include <QGridLayout>
#include <QMessageBox>

void Widget::onInputConfirm() {
  QLineEdit *sideInputs[] = {this->side_a, this->side_b, this->side_c};

  if (!this->triangle) {
    this->triangle = new Triangle();
  }

  sideInputs >> *this->triangle;

  emit valueChanged(this->triangle);
}

void Widget::onInputIncreaseBy() {
  *this->triangle + this->increaseSidesBy->text().toDouble();
  this->increaseSidesBy->clear();

  emit valueChanged(this->triangle);
}

void Widget::onInputIncreaseTimes() {
  (*this->triangle) * (this->increaseSidesTimes->text().toDouble());
  this->increaseSidesTimes->clear();

  emit valueChanged(this->triangle);
}

void Widget::onValueChange(Triangle *triangle) {
  TriangleSides sides = triangle->getSides();
  TriangleHeights heights = triangle->heights();
  TriangleAngles angles = triangle->angles();

  QLineEdit *sideInputs[] = {this->side_a, this->side_b, this->side_c};

  sideInputs << *this->triangle;

  this->triangleInstancesCount->setText(
      QString::number(triangle->getTrianglesCount()));
  this->area->setText(QString::number(triangle->area()));
  this->perimeter->setText(QString::number(triangle->perimeter()));
  this->isRectangular->setText(QVariant(triangle->isRectangular()).toString());

  this->heights->setText(QString("AK: %1\nBK: %2\nCK: %3")
                             .arg(heights.ak)
                             .arg(heights.bk)
                             .arg(heights.ck));

  this->angles->setText(QString("ABC: %1\nBCA: %2\nCAB: %3")
                            .arg(angles.abc)
                            .arg(angles.bca)
                            .arg(angles.cab));
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;

  this->triangle = nullptr;

  this->side_a = new QLineEdit;
  this->side_a->setPlaceholderText("Side A length");

  this->side_b = new QLineEdit;
  this->side_b->setPlaceholderText("Side B length");

  this->side_c = new QLineEdit;
  this->side_c->setPlaceholderText("Side C length");

  this->increaseSidesBy = new QLineEdit;
  this->increaseSidesTimes = new QLineEdit;

  this->isRectangular = new QLineEdit;
  this->isRectangular->setReadOnly(true);

  this->area = new QLineEdit;
  this->area->setReadOnly(true);

  this->perimeter = new QLineEdit;
  this->perimeter->setReadOnly(true);

  this->angles = new QTextEdit;
  this->angles->setReadOnly(true);

  this->heights = new QTextEdit;
  this->heights->setReadOnly(true);

  this->confirmInput = new QPushButton("Enter");
  this->confirmIncreaseBy = new QPushButton("Increase by");
  this->confirmIncreaseTimes = new QPushButton("Increase times");

  this->triangleInstancesCount =
      new QLabel(QString::number(this->triangle->getTrianglesCount()));

  mainLayout->addWidget(this->side_a, 0, 0);
  mainLayout->addWidget(this->side_b, 0, 1);
  mainLayout->addWidget(this->side_c, 0, 2);
  mainLayout->addWidget(this->confirmInput, 1, 0, 1, 3);

  mainLayout->addWidget(new QLabel("Increase sides by:"), 2, 0);
  mainLayout->addWidget(this->increaseSidesBy, 2, 1);
  mainLayout->addWidget(this->confirmIncreaseBy, 2, 2);

  mainLayout->addWidget(new QLabel("Increase sides times:"), 3, 0);
  mainLayout->addWidget(this->increaseSidesTimes, 3, 1);
  mainLayout->addWidget(this->confirmIncreaseTimes, 3, 2);

  mainLayout->addWidget(new QLabel("Is rectangular:"), 4, 0);
  mainLayout->addWidget(this->isRectangular, 4, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Area:"), 5, 0);
  mainLayout->addWidget(this->area, 5, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Perimeter:"), 6, 0);
  mainLayout->addWidget(this->perimeter, 6, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Angles:"), 7, 0);
  mainLayout->addWidget(this->angles, 7, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Heights:"), 8, 0);
  mainLayout->addWidget(this->heights, 8, 1, 1, 2);

  mainLayout->addWidget(this->triangleInstancesCount, 9, 0);

  connect(this->confirmInput, &QPushButton::released, this,
          &Widget::onInputConfirm);

  connect(this->confirmIncreaseBy, &QPushButton::released, this,
          &Widget::onInputIncreaseBy);

  connect(this->confirmIncreaseTimes, &QPushButton::released, this,
          &Widget::onInputIncreaseTimes);

  connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}

#include "widget.h"
#include "src/triangleangles.h"
#include "triangle.h"
#include "trianglesides.h"

#include <QGridLayout>
#include <QMessageBox>

void Widget::onInputConfirm() {
  TriangleSides sides;

  sides.a = this->side_a->text().toDouble();
  sides.b = this->side_b->text().toDouble();
  sides.c = this->side_c->text().toDouble();

  this->triangle = new Triangle(sides);

  emit valueChanged(this->triangle);
}

void Widget::onInputIncrease() {
  this->triangle->increaseSidesBy(this->increaseSidesBy->text().toDouble());

  emit valueChanged(this->triangle);
}

void Widget::onValueChange(Triangle *triangle) {
  TriangleSides sides = triangle->getSides();
  TriangleHeights heights = triangle->heights();
  TriangleAngles angles = triangle->angles();

  this->side_a->setText(QString::number(sides.a));
  this->side_b->setText(QString::number(sides.b));
  this->side_c->setText(QString::number(sides.c));

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

  this->isRectangular = new QLineEdit;
  this->isRectangular->setReadOnly(true);

  this->area = new QLineEdit;
  this->area->setReadOnly(true);

  this->perimeter = new QLineEdit;
  this->perimeter->setReadOnly(true);

  this->angles = new QTextEdit("Angles");
  this->heights = new QTextEdit("Heights");

  this->confirmInput = new QPushButton("Enter");
  this->confirmIncrease = new QPushButton("Increase");

  mainLayout->addWidget(this->side_a, 0, 0);
  mainLayout->addWidget(this->side_b, 0, 1);
  mainLayout->addWidget(this->side_c, 0, 2);
  mainLayout->addWidget(this->confirmInput, 1, 0, 1, 3);

  mainLayout->addWidget(new QLabel("Increase sides by:"), 2, 0);
  mainLayout->addWidget(this->increaseSidesBy, 2, 1);
  mainLayout->addWidget(this->confirmIncrease, 2, 2);

  mainLayout->addWidget(new QLabel("Is rectangular:"), 3, 0);
  mainLayout->addWidget(this->isRectangular, 3, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Area:"), 4, 0);
  mainLayout->addWidget(this->area, 4, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Perimeter:"), 5, 0);
  mainLayout->addWidget(this->perimeter, 5, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Angles:"), 6, 0);
  mainLayout->addWidget(this->angles, 6, 1, 1, 2);

  mainLayout->addWidget(new QLabel("Heights:"), 7, 0);
  mainLayout->addWidget(this->heights, 7, 1, 1, 2);

  connect(this->confirmInput, &QPushButton::released, this,
          &Widget::onInputConfirm);

  connect(this->confirmIncrease, &QPushButton::released, this,
          &Widget::onInputIncrease);

  connect(this, &Widget::valueChanged, &Widget::onValueChange);

  setLayout(mainLayout);
}

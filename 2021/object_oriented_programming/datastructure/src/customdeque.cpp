#include "customdeque.h"
#include <iostream>

const int linkedListExtremum(Node *front,
                             const bool (*comparator)(double, double)) {
  int result;

  for (Node *temp = front; temp != nullptr; temp = temp->next) {
    if (comparator(temp->data, result)) {
      result = temp->data;
    }
  }

  return result;
}

const bool maxValueComparator(double value1, double value2) {
  return value1 > value2;
}

const bool minValueComparator(double value1, double value2) {
  return value1 < value2;
}

const double CustomDeque::getMaxValue() {
  return linkedListExtremum(this->front, maxValueComparator);
}
const double CustomDeque::getMinValue() {
  return linkedListExtremum(this->front, minValueComparator);
}

const double CustomDeque::getAverageValue() {
  double result = 0;
  int i = 0;

  for (Node *temp = front; temp != nullptr; temp = temp->next) {
    result += temp->data;
    i++;
  }

  return result / i;
}

void operator+(double data, CustomDeque &dq) { dq.insertFront(data); }
void operator+(CustomDeque &dq, double data) { dq.insertRear(data); }

void operator-(double data, CustomDeque &dq) { dq.deleteFront(); }
void operator-(CustomDeque &dq, Node *side) { dq.deleteRear(); }

void operator>>(QListWidget *in, CustomDeque &dq) {
  dq.erase();

  for (int i = 0; i < in->count(); i++) {
    in->setCurrentRow(i);
    dq + in->currentItem()->text().toDouble();
  }
}

void operator<<(QListWidget *out, CustomDeque &dq) {
  out->clear();

  for (Node *temp = dq.getFront(); temp != nullptr; temp = temp->next) {
    out->addItem(QString::number(temp->data));
  }
}

void operator>>(QLineEdit *in, CustomDeque &dq) { in->text().toDouble() + dq; };

void operator>>(CustomDeque &dq, QLineEdit *in) { dq + in->text().toDouble(); };

#import "customdeque.h"
#include "deque.h"

enum ValueShouldBe { Smallest = -1, Biggest = 1, Average = 0 };

const int linkedListExtremum(const ValueShouldBe valueShouldBe, Node *front) {
  int result = 0;
  int i = 0;

  for (Node *temp = front; temp != nullptr; temp = temp->next) {
    if (valueShouldBe == ValueShouldBe::Biggest && temp->data > result) {
      result = temp->data;
    }

    if (valueShouldBe == ValueShouldBe::Smallest && temp->data < result) {
      result = temp->data;
    }

    if (valueShouldBe == ValueShouldBe::Average) {
      result += temp->data;
    }
  }

  if (valueShouldBe == ValueShouldBe::Average) {
    return result / i;
  }

  return result;
}

// Could be also implemented using accumulator in class
const auto CustomDeque::getMaxValue() {
  return linkedListExtremum(ValueShouldBe::Biggest, this->front);
}
const auto CustomDeque::getMinValue() {
  return linkedListExtremum(ValueShouldBe::Smallest, this->front);
}

const double CustomDeque::averageValue() {
  return linkedListExtremum(ValueShouldBe::Average, this->front);
}

void operator+(double data, CustomDeque &dq) { dq.insertFront(data); }
void operator+(CustomDeque &dq, double data) { dq.insertRear(data); }

void operator-(double data, CustomDeque &dq) { dq.deleteFront(); }
void operator-(CustomDeque &dq, Node *side) { dq.deleteRear(); }

void operator>>(QTableWidget *in, CustomDeque &dq) {
  dq.erase();

  for (int i = 0; i < in->rowCount(); i++) {
    dq + in->item(i, 0)->text().toDouble();
  }
}

void operator<<(QTableWidget *out, CustomDeque &dq) {
  out->setRowCount(dq.getSize());
  out->setColumnCount(1);

  int i = 0;
  for (Node *temp = dq.getFront(); temp != nullptr; temp = temp->next) {
    QTableWidgetItem *item = new QTableWidgetItem();

    item->setText(QString::number(temp->data));
    out->setItem(i, 0, item);

    i++;
  }
}

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

void operator<<(QLabel *out, CustomDeque &dq) {
  out->clear();

  QString lastFixedQueueText = "Last fixed queue: ";

  for (Node *temp = dq.getFront(); temp != nullptr; temp = temp->next) {
    lastFixedQueueText += QString::number(temp->data) + " ";
  }

  out->setText(lastFixedQueueText);
}

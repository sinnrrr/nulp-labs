#import "customdeque.h"

enum ValueShouldBe { Smallest = -1, Biggest = 1 };

const int linkedListExtremum(const ValueShouldBe valueShouldBe, Node *front) {
  int result = 0;

  for (Node *temp = front; temp != nullptr; temp = temp->next) {
    if (valueShouldBe == ValueShouldBe::Biggest && temp->data > result) {
      result = temp->data;
    }

    if (valueShouldBe == ValueShouldBe::Smallest && temp->data < result) {
      result = temp->data;
    }
  }

  return result;
}

// Could be also implemented using accumulator in class
const int CustomDeque::getMaxValue() {
  return linkedListExtremum(ValueShouldBe::Biggest, this->front);
}
const int CustomDeque::getMinValue() {
  return linkedListExtremum(ValueShouldBe::Smallest, this->front);
}

const double CustomDeque::averageValue() {
  int result = 0;
  int i = 0;

  for (Node *temp = this->front; temp != nullptr; temp = temp->next) {
    result += temp->data;
    i++;
  }

  return (double)result / i;
}

#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using std::vector;

template <typename T> class CustomSet {
  using ElementsType = vector<T>;

private:
  ElementsType elements;

public:
  // iterator interface
  typename ElementsType::iterator begin() { return elements.begin(); }
  typename ElementsType::iterator end() { return elements.end(); }

  CustomSet(ElementsType initial) { this->elements = initial; };

  ElementsType getElements() { return this->elements; }

  void push(T element) {
    if (std::find(std::begin(this->elements), std::end(this->elements),
                  element) != std::end(this->elements)) {
      return; // found duplicate
    }

    this->elements.push_back(element);
  }

  void erase() { this->elements.clear(); }

  void erase(T element) {
    this->elements.erase(std::remove(std::begin(this->elements),
                                     std::end(this->elements), element),
                         std::end(this->element));
  }

  ElementsType intersection(CustomSet<T> *otherSet) {
    ElementsType v1 = this->elements;
    ElementsType v2 = otherSet->getElements();
    ElementsType v3; // Intersection of V1 and V2

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                          back_inserter(v3));

    return v3;
  }
};

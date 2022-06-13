#include <algorithm>
#include <iterator>
#include <vector>

template <typename T> class CustomVector {
  using Elements = std::vector<T>;

private:
  Elements elements;

public:
  CustomVector(Elements input) { this->elements = input; };

  Elements getElements() { return this->elements; };

  Elements removeElement(T elementValue) {
    this->elements.erase(std::remove(std::begin(this->elements),
                                     std::end(this->elements), elementValue));

    return elements;
  };

  Elements changeElement(T operatedValue, T newValue) {
    std::transform(std::begin(elements), std::end(elements),
                   std::begin(elements));
  };
};

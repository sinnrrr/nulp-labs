#include "triangle.h"
#include "triangleangles.h"
#include "trianglesides.h"
#include <cmath>
#include <stdexcept>

//
// Constructor and destructor
//

Triangle::Triangle(TriangleSides sides) {
  if (!this->isValid(sides)) {
    throw std::invalid_argument("Received triangle cannot exist");
  }

  this->setSides(sides);
}

//
// Function definitions
//

bool Triangle::isValid(TriangleSides sides) {
  const auto biggestSide = std::max({sides.a, sides.b, sides.c});
  const auto shortenedSum = sides.a + sides.b + sides.c - biggestSide;

  return shortenedSum > biggestSide;
}

bool Triangle::isRectangular() {
  const double eps = 0.01;

  return fabs(pow(this->sides.c, 2) -
              (pow(this->sides.a, 2) + pow(this->sides.b, 2))) < eps;
};

double Triangle::perimeter() {
  return this->sides.a + this->sides.b + this->sides.c;
}

double Triangle::area() {
  // half-perimeter
  double p = this->perimeter() / 2;

  // hero's formula
  return sqrt(p * (p - this->sides.a) * (p - this->sides.b) *
              (p - this->sides.c));
}

TriangleAngles Triangle::angles() {
  TriangleAngles angles;

  const auto angleFinder = [](const double a, const double b, const double c) {
    return (180. / M_PI) *
           acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
  };

  angles.cab = angleFinder(this->sides.a, this->sides.b, this->sides.c);
  angles.abc = angleFinder(this->sides.a, this->sides.c, this->sides.b);
  angles.bca = angleFinder(this->sides.b, this->sides.c, this->sides.a);

  return angles;
}

TriangleHeights Triangle::heights() {
  TriangleHeights heights;

  auto area = this->area();

  heights.ak = (2 * area) / this->sides.a;
  heights.bk = (2 * area) / this->sides.b;
  heights.ck = (2 * area) / this->sides.c;

  return heights;
}

TriangleSides Triangle::increaseSidesBy(const double by) {
  this->sides.a += by;
  this->sides.c += by;
  this->sides.b += by;

  return this->sides;
}

TriangleSides Triangle::increaseSidesTimes(const double by) {
  this->sides.a *= by;
  this->sides.c *= by;
  this->sides.b *= by;

  return this->sides;
}

//
// Overloads
//

Triangle *Triangle::operator+(const double increaseSidesBy) {
  this->increaseSidesBy(increaseSidesBy);

  return this;
}

Triangle *Triangle::operator*(const double increaseSidesTimes) {
  this->increaseSidesTimes(increaseSidesTimes);

  return this;
}

double Triangle::operator[](const int i) { return *this->sidesMap[i - 1]; }

Triangle::operator double() { return this->area(); }

//
// Friendly overloads
//
const int TRIANGLE_SIDES_COUNT = 3;

void operator<<(QLineEdit *out[TRIANGLE_SIDES_COUNT], TriangleSides &sides) {
  out[0]->setText(QString::number(sides.a));
  out[1]->setText(QString::number(sides.b));
  out[2]->setText(QString::number(sides.c));
};

void operator>>(QLineEdit *in[3], TriangleSides &sides) {
  double *sidesMap[TRIANGLE_SIDES_COUNT] = {&sides.a, &sides.b, &sides.c};

  for (int i = 0; i < TRIANGLE_SIDES_COUNT; i++) {
    *sidesMap[i] = in[i]->text().toDouble();
  }
};

bool operator>(Triangle &tr1, Triangle &tr2) {
  return tr1.area() > tr2.area();
};

bool operator<(Triangle &tr1, Triangle &tr2) {
  return tr1.area() < tr2.area();
};

bool operator==(Triangle &tr1, Triangle &tr2) {
  return tr1.area() == tr2.area();
};

#include "triangle.h"
#include "triangleangles.h"
#include "trianglesides.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

bool Triangle::isValid(TriangleSides sides) {
  const auto biggestSide = std::max({sides.a, sides.b, sides.c});
  const auto shortenedSum = sides.a + sides.b + sides.c - biggestSide;

  if (shortenedSum > biggestSide) {
    return true;
  }

  return false;
}

Triangle::Triangle(TriangleSides sides) {
  if (!this->isValid(sides)) {
    throw std::invalid_argument("Received triangle cannot exist");
  }

  this->setSides(sides);
}

bool Triangle::isRectangular() {
  return pow(this->sides.c, 2) == pow(this->sides.a, 2) + pow(this->sides.b, 2);
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

  const double area = this->area();

  angles.abc = asin(2 * area / this->sides.a * this->sides.b) * (180 / M_PI);
  angles.bca = asin(2 * area / this->sides.b * this->sides.c) * (180 / M_PI);
  angles.cab = asin(2 * area / this->sides.a * this->sides.c) * (180 / M_PI);

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

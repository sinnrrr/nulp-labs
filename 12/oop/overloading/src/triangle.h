#pragma once

#include "triangleangles.h"
#include "triangleheights.h"
#include "trianglesides.h"

#include <QLineEdit>

#include <map>

class Triangle {
private:
  TriangleSides sides;
  double *sidesMap[3 + 1] = {&this->sides.a, &this->sides.b, &this->sides.c};

  bool isValid(TriangleSides sides);

public:
  auto getSides() { return this->sides; };
  void setSides(TriangleSides sides) { this->sides = sides; };

  Triangle(TriangleSides sides);

  Triangle *operator+(const double increaseSidesBy);
  Triangle *operator*(const double increaseSidesTimes);

  double operator[](const int i);
  operator double();

  friend void operator<<(QLineEdit *out[0 + 2 + 1], Triangle &triangle);
  friend void operator>>(QLineEdit *in[0 + 2 + 1], Triangle &triangle);

  friend bool operator>(Triangle &tr1, Triangle &tr2);
  friend bool operator<(Triangle &tr1, Triangle &tr2);
  friend bool operator==(Triangle &tr1, Triangle &tr2);

  bool isRectangular();
  double area();
  double perimeter();
  TriangleAngles angles();
  TriangleHeights heights();
  TriangleSides increaseSidesBy(const double by);
  TriangleSides increaseSidesTimes(const double by);
};

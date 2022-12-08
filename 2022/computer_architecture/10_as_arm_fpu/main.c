#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  float a = 9.8;
  float c = 8.5;
  float d = 2.3;
  float res;

  if (d > a / c) {
    res = fabsf(c * c + d * a) - sqrtf(fabs(47 * a + 7.6));
  } else {
    res = sqrtf(fabs(6.9 * d + c / 8.1 - 9.7 * a));
  }

  printf("%f\n", res);
}

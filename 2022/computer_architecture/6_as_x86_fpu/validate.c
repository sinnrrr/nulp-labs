#include <math.h>
#include <stdio.h>

int main() {
  double a = 9.8, c = 8.5, d = 2.3;
  double res = (fabs(c * c + d * a) - sqrt(47 * a + 7.6)) /
               (6.9 * d + c / 8.1 - 9.7 * a);

  printf("The result is: %f\n\n\n", res);
  return 0;
}

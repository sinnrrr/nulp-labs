#include <math.h>
#include <stdio.h>
#include "calculations.h"

int main(void)
{
    const double START = 0, END = M_PI;
    double x = START, y = 0, step;

    printf("Enter step: ");
    scanf("%lf", &step);

    while (END > x)
    {
        y = calculateArgument(x);

        tabulate(x, y);

        x += step;
    }

    return 0;
}
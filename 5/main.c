#include <math.h>
#include <stdio.h>

#include "calculations.h"

int main(void)
{
    const double START = 0, END = M_PI;
    double step;

    printf("Enter step: ");
    scanf("%lf", &step);

    tabulate(START, END, step);

    return 0;
}
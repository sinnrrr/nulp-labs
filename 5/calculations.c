#include <math.h>
#include <stdio.h>

double calculateArgument(double x)
{
    return pow(cos(x), 4);
}

void tabulate(double x, double y)
{
    printf("% .10lf\t% .10lf\t\n", x, y);
}
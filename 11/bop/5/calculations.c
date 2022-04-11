#include <math.h>
#include <stdio.h>

double calculateArgument(double x)
{
    return pow(cos(x), 4);
}

short argumentRange(double x, double *y)
{
    *y = calculateArgument(x);

    if (y < 0)
    {
        return -1;
    }

    if (y > 0)
    {
        return 1;
    }

    return 0;
}

void tabulate(double start, double end, double step)
{
    short range;
    double x = start, y1 = 0, y2;

    while (end > x)
    {
        y1 = calculateArgument(x);
        range = argumentRange(x, &y2);

        printf("% .10lf\t% .10lf\t% .10lf\t %hd\n", x, y1, y2, range);

        x += step;
    }
}
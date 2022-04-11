#include <math.h>
#include <stdio.h>

int main(void)
{
    double start, end, step, eps;

    printf("Enter start, end, step and eps: ");
    scanf("%lf %lf %lf %lf", &start, &end, &step, &eps);

    if (fabs(start) >= 1 || fabs(end) >= 1)
    {
        puts("Start or end should be in range of -1 and 1");

        return 1;
    }

    for (double x = start; x < end; x += step)
    {
        double currentAddition = 1, teylorCalculationResult = 1;
        double formulaCalculationResult = pow(1 - x, -0.5);

        for (int i = 2; fabs(currentAddition) > eps; i += 2)
        {
            // Division causes conversion to int, so staying with double
            currentAddition *= ((double)(i - 1) / i) * x;
            teylorCalculationResult += currentAddition;
        }

        double calculationsDelta = fabs(formulaCalculationResult - teylorCalculationResult);

        printf(
            "x: %g formula: %lf teylor: %lf delta: %lf\n",
            x,
            formulaCalculationResult,
            teylorCalculationResult,
            calculationsDelta);
    }

    return 0;
}

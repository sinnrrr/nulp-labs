#include <stdio.h>

int calculateBinominalCoefficient(int m, int n)
{
    if (m == 0 || m == n)
    {
        return 1;
    }

    int result = calculateBinominalCoefficient(m, n - 1) + calculateBinominalCoefficient(m - 1, n - 1);

    return result;
}

int main(void)
{
    int m, n;

    printf("Enter m and n: ");
    scanf("%d %d", &m, &n);

    if (m > n)
    {
        puts("Please, enter valid asset of numbers");

        return 1;
    }

    printf("Result: %d\n", calculateBinominalCoefficient(m, n));

    return 0;
}
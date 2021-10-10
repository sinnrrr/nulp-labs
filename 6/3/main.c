#include <stdio.h>

int productOfNumberDigits(int number)
{
    int product = 1, rem;

    while (number != 0)
    {
        rem = number % 10;
        product *= rem;
        number /= 10;
    }

    return product;
}

int main(void)
{
    int inputNumber, result = 0;

    printf("Enter number: ");
    scanf("%d", &inputNumber);

    for (int i = 10; result == 0; i++)
    {
        if (productOfNumberDigits(i) == inputNumber)
        {
            result = i;
        }
    }

    printf("Result: %d", result);

    return 0;
}
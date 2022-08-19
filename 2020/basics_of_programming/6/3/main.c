#include <stdio.h>

#define PRODUCT_OF_NUMBER_DIGITS(number) (number % 10 + (number / 10) % 100 + (number / 100) % 1000)

int main(void)
{
    int number;

    printf("Enter number: ");
    scanf("%d", &number);

    printf("Result: %d", PRODUCT_OF_NUMBER_DIGITS(number));

    return 0;
}
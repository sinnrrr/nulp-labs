#include <stdio.h>
#include <string.h>

int main(void)
{
    int number, reversed = 0, last;

    printf("Enter number: ");
    scanf("%d", &number);

    while (number != 0)
    {
        last = number % 10;
        reversed = reversed * 10 + last;
        number /= 10;
    }

    printf("Result: %d", reversed);

    return 0;
}
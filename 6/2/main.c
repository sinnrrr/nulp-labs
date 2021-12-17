#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static const int EXCLUDE_NUMBER = 7;

int numberIncludes(int includes, int number)
{
    while (number != 0)
    {
        if (number % 10 == includes)
        {
            return 1;
        }

        number /= 10;
    }

    return 0;
}

void outputOddAndWhitlistedNumbers(int size, ...)
{
    va_list arguments;

    printf("Correct numbers: ");

    va_start(arguments, size);
    for (int x = 0; x < size; x++)
    {
        int argument = va_arg(arguments, int);

        // If number is even, don't include excluded number and is not 1.
        if (argument != -1 && (argument % 2 == 0) && !numberIncludes(EXCLUDE_NUMBER, argument))
        {
            printf("%d", argument);
        }
    }
    va_end(arguments);
}

int main(void)
{
    int NUMBERS_PROVIDED = 4;
    
    outputOddAndWhitlistedNumbers(NUMBERS_PROVIDED, 47, 5, 4, -1);

    return 0;
}
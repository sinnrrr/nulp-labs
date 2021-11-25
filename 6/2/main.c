#include <stdio.h>

static const int EXCLUDE_NUMBER = 7;

unsigned short numberIncludes(int includes, int number)
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

int main(void)
{
    int argsNum;

    printf("Enter number of arguments: ");
    scanf("%d", &argsNum);

    int args[argsNum], correctNumbers[argsNum];
    int index = 0;

    for (int i = 0; i < argsNum; i++)
    {
        printf("Enter number for %d array position: ", i);
        scanf("%d", &args[i]);

        // If number is even, and don't include excluded number.
        if ((args[i] % 2 == 0) && !numberIncludes(EXCLUDE_NUMBER, args[i]))
        {
            correctNumbers[index++] = args[i];
        }
    }

    if (index != 0)
    {
        puts("\nResult: ");
        for (int i = 0; i < index; i++)
        {
            printf("%d ", correctNumbers[i]);
        }
    }
    else
    {
        puts("No correct numbers");
    }

    return 0;
}
#include <math.h>
#include <stdio.h>

int main(void)
{
    unsigned int argsNum;

    printf("Enter number of arguments (minimum - 2): ");
    scanf("%d", &argsNum);

    if (argsNum < 2)
    {
        puts("Vector should have minimum 2 elements to proceed");
        return 1;
    }

    unsigned int vector[argsNum], formattedVector[argsNum / 2];
    unsigned int index = 0;

    for (int i = 0; i < argsNum; i++)
    {
        printf("Enter number for %d array position: ", i);
        scanf("%d", &vector[i]);

        if (i >= 1)
        {
            formattedVector[index++] = sqrt(vector[i] * vector[i - 1]);
        }
    }

    puts("New vector:");
    for (int i = 0; i < index; i++)
    {
        printf("%d ", formattedVector[i]);
    }

    return 0;
}
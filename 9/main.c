#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;

    printf("Enter size of square matrix: ");
    scanf("%d", &size);

    int **matrix = (int *)calloc(size, 1 + sizeof(int *));
    if (matrix == NULL)
    {
        puts("Memory for rows is not allocated");

        return 1;
    }

    for (int row = 0; row < size; row++)
    {
        matrix[row] = calloc(size, sizeof(int));
        if (matrix[row] == NULL)
        {
            printf("Memory for column %d is not allocated", row);

            return 1;
        }

        for (int column = 0; column < size; column++)
        {
            int value;

            printf("Enter element for %d %d position: ", row + 1, column + 1);
            scanf("%d", &value);

            matrix[row][column] = value;
        }
    }

    int maxSum = 0, maxSumColumnIndex;

    // starting from second column
    for (int column = 1; column < size; column++)
    {
        int currentSum = 0;
        int diagonalItemRowIndex = column;

        for (int row = 0; row < diagonalItemRowIndex; row++)
        {
            currentSum += matrix[row][column];

            if (currentSum > maxSum)
            {
                maxSum = currentSum;
                maxSumColumnIndex = column + 1;
            }
        }
    }

    printf("Max sum column index: %d\n", maxSumColumnIndex);

    return 0;
}
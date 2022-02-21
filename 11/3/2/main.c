#include <stdio.h>
#include <stdlib.h>

static const int MATRIX_SIZE = 5;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Is being used to sort diagonal values in ascending order
void selectionSort(int values[], int size)
{
    int minimalValueId;

    for (int i = 0; i < size - 1; i++)
    {
        minimalValueId = i;

        for (int j = i + 1; j < size; j++)
        {
            if (values[j] < values[minimalValueId])
            {
                minimalValueId = j;
            }
        }

        swap(&values[minimalValueId], &values[i]);
    }
}

int main(void)
{
    int diagonalValues[MATRIX_SIZE];
    int matrix[MATRIX_SIZE][MATRIX_SIZE];

    // Matrix input
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            printf("Enter the %d element of %d row: ", j + 1, i + 1);
            scanf("%d", &matrix[i][j]);

            if (i == j)
            {
                diagonalValues[i] = matrix[i][j];
            }
        }
    }

    selectionSort(diagonalValues, sizeof(diagonalValues) / sizeof(diagonalValues[0]));

    // The size of matrix correlates with amount of diagonal elements
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        matrix[i][i] = diagonalValues[i];
    }

    return 0;
}
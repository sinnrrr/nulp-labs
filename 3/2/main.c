#include <stdio.h>
#include <stdlib.h>

const int MATRIX_SIZE = 5;

int diagonal_values[MATRIX_SIZE];
int matrix[MATRIX_SIZE][MATRIX_SIZE];

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Is being used to sort diagonal values in ascending order
void selectionSort()
{
    int minimal_value_id;
    int n = sizeof(matrix) / sizeof(matrix[0]);

    for (int i = 0; i < n - 1; i++)
    {
        minimal_value_id = i;

        for (int j = i + 1; j < n; j++)
        {
            if (matrix[j] < matrix[minimal_value_id])
            {
                minimal_value_id = j;
            }
        }

        swap(&matrix[minimal_value_id], &matrix[i]);
    }
}

// Saves user input matrix and array of diagonal values
void askMatrixInput()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            printf("Enter the %d element of %d row: ", j + 1, i + 1);
            scanf("%d", &matrix[i][j]);

            if (i == j)
            {
                diagonal_values[i] = matrix[i][j];
            }
        }
    }
}

void outputDiagonalValues()
{
    printf("\nResults: \n");

    // The size of matrix correlates with amount of diagonal elements
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        printf("%d ", diagonal_values[i]);
    }
}

int main(void)
{
    askMatrixInput();
    selectionSort();
    outputDiagonalValues();

    return 0;
}
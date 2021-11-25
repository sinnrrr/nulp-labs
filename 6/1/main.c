#include <stdio.h>

int dotProduct(int v[], int u[], int n)
{
    int result = 0;

    for (int i = 0; i < n; i++)
    {
        result += v[i] * u[i];
    }

    return result;
}

int isAllZeros(int n, int arr[n])
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
        {
            return 0;
        }
    }

    return 1;
}

int isOrthogonal(int rowCount, int columnCount, int matrix[rowCount][columnCount])
{
    int matrixResults[rowCount];

    for (int i = 0; i < rowCount; i++)
    {
        int rowResults[rowCount];

        for (int j = 0; j < rowCount; j++)
        {
            int result = dotProduct(matrix[i], matrix[j], columnCount);

            if ((i == j && result == 0) || result != 0)
            {
                rowResults[j] = 0;
            }
            else
            {
                return 1;
            }
        }

        matrixResults[i] = isAllZeros(rowCount, rowResults);
    }

    return isAllZeros(rowCount, matrixResults);
}

int main(void)
{
    int rowCount, columnCount;

    printf("Enter count of rows and columns: ");
    scanf("%d %d", &rowCount, &columnCount);

    int matrix[rowCount][columnCount];

    for (int row = 0; row < rowCount; row++)
    {
        for (int column = 0; column < columnCount; column++)
        {
            int value;

            printf("Enter element for %d %d position: ", row + 1, column + 1);
            scanf("%d", &value);

            matrix[row][column] = value;
        }
    }

    puts(isOrthogonal(rowCount, columnCount, matrix) ? "Is orthogonal" : "Is not orthogonal");

    return 0;
}
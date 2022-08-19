#include <stdio.h>
#include <string.h>

int main(void)
{
    int rowCount, columnCount;

    printf("Enter count of rows and columns: ");
    scanf("%d %d", &rowCount, &columnCount);

    int matrix[rowCount][columnCount];

    int nullCount[rowCount];
    memset(nullCount, 0, sizeof(nullCount));

    for (int row = 0; row < rowCount; row++)
    {
        for (int column = 0; column < columnCount; column++)
        {
            int value;

            printf("Enter element for %d %d position: ", row + 1, column + 1);
            scanf("%d", &value);

            matrix[row][column] = value;

            if (value == 0) nullCount[row]++;
        }
    }

    for (int row = 0; row < rowCount; row++)
    {
        printf("%d", nullCount[row]);
    }

    return 0;
}
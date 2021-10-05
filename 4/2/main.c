#include "../calculation/calculation.h"
#include <stdio.h>
#include <stdlib.h>

const int FILENAME_LENGTH = 64;

void writeToFile(char filename[FILENAME_LENGTH], unsigned short isBinary, struct Record record)
{
    FILE *file = fopen(filename, "w");

    if (isBinary)
    {
        fwrite(&record, sizeof(record), 1, file);
    } else {
        fprintf(file, );
    }

    fclose(file);
}

void readFromFile(char filename[FILENAME_LENGTH], unsigned short isBinary, struct Record *record)
{
}

int main(void)
{
    struct Record record;
    char filename[FILENAME_LENGTH];
    unsigned short isBinary, isDebugMode;

    printf("Should the program work in debug mode (1 - yes, 0 - no): ");
    scanf("%hu", &isDebugMode);

    if (isDebugMode)
    {
        printf("Enter x, y, u: ");
        scanf("%lf %lf %lf", &record.x, &record.y, &record.u);
    }

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("File in binary? (1 - yes, 0 - no): ");
    scanf("%hu", &isBinary);

    if (isDebugMode)
    {
        writeToFile(filename, isBinary, record);
    }
    else
    {
        readFromFile(filename, isBinary, &record);
    }

    printf("Result: %lf", calculateWithFormula(record));

    return 0;
}
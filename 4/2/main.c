#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "../../1/2/calculation.h"

static const int FILENAME_LENGTH = 64;
static const char *LOG_FILENAME = "data.log";

void writeResultToFile(char filename[FILENAME_LENGTH], unsigned short isBinary, double result)
{
    FILE *file = fopen(filename, "w");

    if (isBinary)
    {
        fwrite(&result, sizeof(result), 1, file);
    }
    else
    {
        fprintf(file, "%lf", result);
    }

    fclose(file);
}

void readParametersFromFile(char filename[FILENAME_LENGTH], struct Record *record)
{
    FILE *file = fopen(filename, "r");

    while (fread(record, sizeof(struct Record), 1, file))
    {
        printf("l");
    }

    fclose(file);
}

void logToFile(const char *text, ...)
{
    va_list args;
    va_start(args, text);

    char *formattedString;
    vasprintf(&formattedString, text, args);

    va_end(args);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char timePrefix[20];
    strftime(timePrefix, sizeof(timePrefix), "%F %X", tm);

    FILE *file = fopen(LOG_FILENAME, "a");

    fprintf(file, "[%s] %s\n", timePrefix, text);
    fclose(file);
}

int main(void)
{
    double result;
    struct Record record;
    unsigned short isBinary;
    char filename[FILENAME_LENGTH];

    logToFile("Program started.");

    printf("Enter filename (max 63 characters): ");
    scanf("%s", filename);

    if (access(filename, F_OK) == 0)
    {
        readParametersFromFile(filename, &record);
        logToFile("Parameters file \"%s\" opened. X=%lf, Y=%lf, U=%lf.", filename, &record.x, &record.y, &record.u);
    }
    else
    {
        printf("Enter x, y, u: ");
        scanf("%lf %lf %lf", &record.x, &record.y, &record.u);
    }

    printf("Should result file be in binary? (1 - yes, 0 - no): ");
    scanf("%hu", &isBinary);

    result = calculateWithFormula(record);
    logToFile("Expression calculated. Result = %lf.", &result);

    writeResultToFile(filename, isBinary, result);
    logToFile("Output file \"%s\" saved.", filename);
    printf("Result: %lf", result);

    logToFile("Program ended.");

    return 0;
}
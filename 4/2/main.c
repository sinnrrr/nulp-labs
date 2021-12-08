#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "../../1/2/calculations.h"

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

void writeParametersToFile(char filename[FILENAME_LENGTH], struct Record record)
{
    FILE *file = fopen(filename, "w");

    fwrite(&record, sizeof(record), 1, file);
    fclose(file);
}

int readParametersFromFile(char filename[FILENAME_LENGTH], struct Record *record)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return 1;
    }

    fread(record, sizeof(struct Record), 1, file);
    fclose(file);

    return 0;
}

void logToFile(const char *format, ...)
{
    char *formattedString;
    va_list args;

    va_start(args, format);
    vasprintf(&formattedString, format, args);
    va_end(args);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char timePrefix[20];
    strftime(timePrefix, sizeof(timePrefix), "%F %X", tm);

    FILE *file = fopen(LOG_FILENAME, "a");

    fprintf(file, "[%s] %s\n", timePrefix, formattedString);
    fclose(file);
}

int main(void)
{
    double result;
    struct Record record;
    unsigned short isBinary;
    char paramsFilename[FILENAME_LENGTH], resultFilename[FILENAME_LENGTH];

    logToFile("Program started.");

    printf("Enter params filename (max 63 characters): ");
    scanf("%s", paramsFilename);

    if (access(paramsFilename, F_OK) == 0)
    {
        if (!readParametersFromFile(paramsFilename, &record))
        {
            puts("Failed opening parameters file.");
        }

        logToFile("Parameters file \"%s\" opened. X=%lf, Y=%lf, U=%lf.", paramsFilename, record.x, record.y, record.u);
    }
    else
    {
        printf("Enter x, y, u: ");
        scanf("%lf %lf %lf", &record.x, &record.y, &record.u);

        writeParametersToFile(paramsFilename, record);
        logToFile("Parameters file \"%s\" opened. X=%lf, Y=%lf, U=%lf.", paramsFilename, record.x, record.y, record.u);
    }

    printf("Enter result filename (max 63 characters): ");
    scanf("%s", resultFilename);

    printf("Should result file be in binary? (1 - yes, 0 - no): ");
    scanf("%hu", &isBinary);

    result = calculateWithFormula(record);
    logToFile("Expression calculated. Result = %lf.", &result);

    writeResultToFile(resultFilename, isBinary, result);
    logToFile("Output file \"%s\" saved.", resultFilename);
    printf("Result: %lf", result);

    logToFile("Program ended.");

    return 0;
}
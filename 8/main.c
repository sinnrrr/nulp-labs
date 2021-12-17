#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define DELIMITER "|"
#define BUFFER_LENGTH 255

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("Entered file does not exist");

        return 1;
    }

    const int fileLinesCount = countFileLines(fp);
    struct Book books[fileLinesCount];
    char buffer[BUFFER_LENGTH];

    for (int i = 0; i < fileLinesCount; i++)
    {
        fgets(buffer, BUFFER_LENGTH, fp);
        printf("%s\n", buffer);

        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        books[i] = parseToBook(buffer, DELIMITER);
    }

    fclose(fp);

    return 0;
}

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

    struct Book books[BUFFER_LENGTH];
    char buffer[BUFFER_LENGTH];

    int linesCount = 0;
    for (; fgets(buffer, BUFFER_LENGTH, fp); linesCount++)
    {
        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        books[linesCount] = parseToBook(buffer, DELIMITER);
    }

    fclose(fp);

    selectionSort(books, linesCount);

    puts("Result:");
    for (int i = 0; i < linesCount; i++)
    {
        printf("%s %s %d %d %f\n", books[i].author, books[i].name, books[i].publicationYear, books[i].pagesCount, books[i].price);
    }

    return 0;
}

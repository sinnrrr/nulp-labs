#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "utils.h"

#define DELIMITER "|"
#define BUFFER_LENGTH 255

int countFileLines(FILE *fp)
{
    int lines = 0, ch = 0;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }

    return lines;
}

int comparator(const void *a, const void *b)
{
    Book *book1 = (Book *)a;
    Book *book2 = (Book *)b;

    return book2->price - book1->price;
}

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("Entered file does not exist");

        return 1;
    }

    Book books[BUFFER_LENGTH];
    char buffer[BUFFER_LENGTH];

    int linesCount = 0;
    for (; fgets(buffer, BUFFER_LENGTH, fp); linesCount++)
    {
        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        parseToBook(&books[linesCount], buffer, DELIMITER);
    }

    fclose(fp);

    Book filteredBooks[linesCount];
    int i = 0, filteredBooksCount = 0;
    for (; i < linesCount; i++)
    {
        if (books[i].publicationYear < 1975)
        {
            filteredBooks[filteredBooksCount++] = books[i];
        }
    }

    qsort(filteredBooks, sizeof(filteredBooks) / sizeof(filteredBooks[0]), sizeof(filteredBooks[0]), comparator);

    puts("Result:");
    for (int i = 0; i < filteredBooksCount; i++)
    {
        printf("%s %s %d %d %f\n", filteredBooks[i].author, filteredBooks[i].name, filteredBooks[i].publicationYear, filteredBooks[i].pagesCount, filteredBooks[i].price);
    }

    return 0;
}

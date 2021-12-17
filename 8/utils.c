#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "book.h"

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

struct Book parseToBook(char *buffer, char *delimiter)
{
    struct Book book;

    char *token = strtok(buffer, delimiter);
    for (int i = 0; token != NULL; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(book.author, token);
            break;
        case 1:
            strcpy(book.name, token);
            break;
        case 2:
            book.publicationYear = atoi(token);
            break;
        case 3:
            book.pagesCount = atoi(token);
            break;
        case 4:
            book.price = atof(token);
            break;
        }

        token = strtok(NULL, delimiter);
    }

    return book;
}

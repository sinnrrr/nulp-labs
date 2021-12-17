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
            printf("Author: %s", token);
            book.author = token;
            break;
        case 1:
            printf("Name: %s", token);
            book.name = token;
            break;
        case 2:
            printf("Pubyear: %s", token);
            book.publicationYear = atoi(token);
            break;
        case 3:
            printf("Pages: %s", token);
            book.pagesCount = atoi(token);
            break;
        case 4:
            printf("Price: %s", token);
            book.price = atoi(token);
            break;
        }

        token = strtok(NULL, delimiter);
    }

    return book;
}

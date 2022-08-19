#include <stdlib.h>
#include <string.h>

#include "main.h"

void parseToBook(Book* book, char *buffer, char *delimiter)
{
    char *token = strtok(buffer, delimiter);
    for (int i = 0; token != NULL; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(book->author, token);
            break;
        case 1:
            strcpy(book->name, token);
            break;
        case 2:
            book->publicationYear = atoi(token);
            break;
        case 3:
            book->pagesCount = atoi(token);
            break;
        case 4:
            book->price = atof(token);
            break;
        }

        token = strtok(NULL, delimiter);
    }
}

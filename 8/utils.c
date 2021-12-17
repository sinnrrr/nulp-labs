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

void swap(struct Book *xp, struct Book *yp)
{
    struct Book temp = *xp;

    *xp = *yp;
    *yp = temp;
}

void selectionSort(struct Book values[], int size)
{
    int minimalValueId;
    for (int i = 0; i < size - 1; i++)
    {
        minimalValueId = i;

        for (int j = i + 1; j < size; j++)
        {
            if (values[j].price > values[minimalValueId].price)
            {
                minimalValueId = j;
            }
        }

        swap(&values[minimalValueId], &values[i]);
    }
}

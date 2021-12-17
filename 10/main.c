#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../8/book.h"
#include "../8/utils.h"

#define DELIMITER "|"
#define BUFFER_LENGTH 255

struct Node
{
    struct Book data[BUFFER_LENGTH];
    struct Node *next;
};

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("Entered file does not exist");

        return 1;
    }

    struct Node list[BUFFER_LENGTH];
    char buffer[BUFFER_LENGTH];

    int linesCount = 0;
    struct Node* previousNode = NULL;
    for (; fgets(buffer, BUFFER_LENGTH, fp); linesCount++)
    {
        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        struct Node currentNode = { parseToBook(buffer, DELIMITER) };
        list[linesCount] = currentNode;
        list[linesCount - 1].next = &currentNode;
    }

    fclose(fp);

    selectionSort(books, linesCount);
}
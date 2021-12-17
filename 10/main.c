#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../8/utils.h"

#define DELIMITER "|"
#define BUFFER_LENGTH 255

struct Node
{
    struct Book data[BUFFER_LENGTH];
    struct Node *next;
};

int comparator(const void *a, const void *b)
{
    struct Node* node1 = (struct Node*)a;
    struct Node* node2 = (struct Node*)b;

    int difference = node2->data->price - node1->data->price;
    
    //// if difference is less then zero, the first and second node will swap 
    // if (difference < 0) {
    //     node1->next = 
    // }

    return difference;
}

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
    struct Node *previousNode = NULL;
    for (; fgets(buffer, BUFFER_LENGTH, fp); linesCount++)
    {
        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        struct Node currentNode = {parseToBook(buffer, DELIMITER), NULL};

        list[linesCount] = currentNode;
        list[linesCount - 1].next = &currentNode;
    }

    fclose(fp);

    qsort(list, sizeof(list) / sizeof(list[0]), sizeof(list[0]), comparator);

    // puts("Result:");
    // for (int i = 0; i < linesCount; i++)
    // {
    //     printf("%s %s %d %d %f\n", list[i]->data.author, books[i].name, books[i].publicationYear, books[i].pagesCount, books[i].price);
    // }

    return 0;
}
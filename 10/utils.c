#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../8/main.h"
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

void outputLinkedList(Node *node)
{
    while (node)
    {
        printf("%s %s %d %d %f\n", node->data.author, node->data.name, node->data.publicationYear, node->data.pagesCount, node->data.price);

        node = node->next;
    }
}

void sortedInsert(Node **head, Node *newNode, int (*comparator)(Node *a, Node *b))
{
    if (!*head || comparator(*head, newNode) <= 0)
    {
        newNode->next = *head;
        *head = newNode;

        return;
    }

    struct Node *current = *head;
    while (current->next && comparator(current->next, newNode) > 0)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

Node *newNode(Book data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->next = NULL;

    return node;
}

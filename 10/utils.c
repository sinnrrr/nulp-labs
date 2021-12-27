#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../8/main.h"
#include "main.h"

void parseToBook(Book *book, char *buffer, char *delimiter)
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

void outputLinkedList(Node *iterator)
{
    while (iterator)
    {
        printf("%s %s %d %d %f\n", iterator->data.author, iterator->data.name, iterator->data.publicationYear, iterator->data.pagesCount, iterator->data.price);

        Node *temp = iterator->next;
        free(iterator);

        iterator = temp;

        free(temp);
    }
}

void sortedInsert(Node **head, Node *newNode, int (*comparator)(const Node *, const Node *))
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

void detachNode(Node **head, Node *detachingNode)
{
    if (!*head || !detachingNode)
    {
        return;
    }

    Node *temp = NULL;
    if (*head == detachingNode)
    {
        temp = *head;
        *head = (*head)->next;

        free(temp);

        return;
    }

    Node *current = *head;
    while (current)
    {
        if (current->next == detachingNode)
        {
            temp = current->next;
            current->next = current->next->next;

            free(temp);

            return;
        }

        current = current->next;
    }
}

void deleteAllMatching(Node **head, int (*matcher)(const Node *))
{
    Node *iterator = *head;
    while (iterator)
    {
        if (matcher(iterator))
        {
            detachNode(head, iterator);
        }

        iterator = iterator->next;
    }
}

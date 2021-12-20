#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

int comparator(const Node *node1, const Node *node2)
{
    return node1->data.price - node2->data.price;
}

int matcher(const Node *node) 
{
    return node->data.publicationYear < (CURRENT_YEAR - YEARS_BEFORE);
}

void readStudentsFromFile(Node **head)
{
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("Entered file does not exist");
        exit(1);
    }

    char buffer[BUFFER_LENGTH];
    for (int i = 0; fgets(buffer, BUFFER_LENGTH, fp); i++)
    {
        Node *temp = (Node *)malloc(sizeof(Node));

        // Remove newline character from the end of buffer (if it exists)
        char *newline = strchr(buffer, '\n');
        if (newline)
        {
            *newline = 0;
        }

        // Parse string to Book struct
        parseToBook(&temp->data, buffer, DELIMITER);

        // Filtering conditionals
        if (temp->data.publicationYear > 1975)
        {
            continue;
        }

        sortedInsert(head, temp, comparator);
    }

    fclose(fp);
}

int main(void)
{
    Node *head = NULL;

    puts("Before:");
    readStudentsFromFile(&head);
    outputLinkedList(head);
    printf("\n");

    puts("After:");
    deleteAllMatching(&head, matcher);
    outputLinkedList(head);
    printf("\n");

    return 0;
}

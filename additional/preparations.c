#include <stdio.h>
#include <stdlib.h>

typedef struct Data
{
    int n;
} Data;

typedef struct Node
{
    Data data;
    struct Node *next;
} Node;

int comparator(const Node *node1, const Node *node2)
{
    return node2->data.n - node1->data.n;
}

Node *newNode(Data data)
{
    Node *node = (Node *)malloc(sizeof(struct Node));

    node->data = data;
    node->next = NULL;

    return node;
}

Node *fintMaxElementMatching(Node *head, int (*comparator)(const Node *, const Node *))
{
    Node *maxValueNode = NULL;

    Node *iterator = head;
    while (iterator)
    {
        if (!maxValueNode)
        {
            maxValueNode = iterator;

            continue;
        }

        if (comparator(maxValueNode, iterator) > 0)
        {
            maxValueNode = iterator;
        }

        iterator = iterator->next;
    }

    return maxValueNode;
}

void outputLinkedList(Node *iterator)
{
    while (iterator)
    {
        printf("%d\n", iterator->data.n);

        iterator = iterator->next;
    }
}

void unshift(Node **head, Node *operand)
{
    if (!*head)
    {
        *head = operand;

        return;
    }

    operand->next = *head;
    *head = operand;
}

void append(Node **head, Node *operand)
{
    if (!*head)
    {
        *head = operand;

        return;
    }

    Node *iterator = *head;
    while (iterator->next)
    {
        iterator = iterator->next;
    }

    iterator->next = operand;
}

void insertAfter(Node *previousNode, Node *operand)
{
    if (!previousNode)
    {
        return;
    }

    operand->next = previousNode->next;
    previousNode->next = operand;
}

void swapNodes(Node *head, Node *node1, Node *node2)
{
    if (node1 == node2)
    {
        return;
    }

    Node *node1Next = NULL, *node1Previous = NULL, *node2Next = NULL, *node2Previous = NULL;

    Node *iterator = head;
    while (iterator || (node1Next && node1Previous && node2Next && node2Previous))
    {
        if (iterator->next == node1)
        {
            node1Previous = iterator;
            node1Next = iterator->next->next;

            continue;
        }

        if (iterator->next == node2)
        {
            node2Previous = iterator;
            node2Next = iterator->next->next;

            continue;
        }

        iterator = iterator->next;
    }

    node1Previous->next = node2;
    node2->next = node1Next;

    node2Previous->next = node1;
    node1->next = node2Next;
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

void freeList(Node *head)
{
    Node *temp;

    while (head)
    {
        temp = head;
        head = head->next;

        free(temp);
    }
}

int main(void)
{
    Node *head = newNode((Data){.n = 1});
    Node *second = newNode((Data){.n = 2});
    Node *third = newNode((Data){.n = 3});
    Node *fourth = newNode((Data){.n = 4});
    Node *fifth = newNode((Data){.n = 5});

    head->next = fourth;

    unshift(&head, second);
    append(&head, third);
    insertAfter(head, fifth);

    printf("%d\n\n", fintMaxElementMatching(head, comparator)->data.n);

    // swapNodes(head, fourth, third);

    outputLinkedList(head);

    return 0;
}

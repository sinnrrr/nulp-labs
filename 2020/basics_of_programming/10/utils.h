#include "../8/main.h"
#include "main.h"

extern void parseToBook(Book *book, char *buffer, char *delimiter); 

extern void outputLinkedList(Node *head);

extern void sortedInsert(Node **head, Node *newNode, int (*comparator)(const Node *, const Node *));

extern void deleteAllMatching(Node **head, int (*matcher)(const Node *));

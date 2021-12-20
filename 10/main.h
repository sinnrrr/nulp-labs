#define DELIMITER "|"
#define BUFFER_LENGTH 255

typedef struct Node
{
    Book data;
    struct Node *next;
} Node;

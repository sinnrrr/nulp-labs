#define DELIMITER "|"
#define BUFFER_LENGTH 255

#define CURRENT_YEAR 2021
#define YEARS_BEFORE 5

typedef struct Node
{
    Book data;
    struct Node *next;
} Node;

#include <stdio.h>

#include "book.h"

extern int countFileLines(FILE *fp);

extern int comparator(const void *a, const void *b);

extern struct Book parseToBook(char *buffer, char *delimiter);

#include <stdio.h>

#include "book.h"

extern int countFileLines(FILE *fp);

extern struct Book parseToBook(char *buffer, char *delimiter);

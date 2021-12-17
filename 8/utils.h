#include <stdio.h>

#include "book.h"

extern void swap(struct Book *xp, struct Book *yp);

extern void selectionSort(struct Book values[], int size);

extern int countFileLines(FILE *fp);

extern struct Book parseToBook(char *buffer, char *delimiter);

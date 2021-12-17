#include <stdio.h>
#include <time.h>

#include "sorting.h"
#include "utils.h"

int main(void)
{
    long elementsNumber;

    printf("Enter the number of array elements: ");
    scanf("%ld", &elementsNumber);

    long arr1[elementsNumber], arr2[elementsNumber];

    fillArraysWithRandomItems(elementsNumber, arr1, arr2);

    puts("\nBefore sorting");

    printf("Array1 is ordered: %d\n", arrayIsOrdered(elementsNumber, arr1));
    printf("Array2 is ordered: %d\n", arrayIsOrdered(elementsNumber, arr2));

    printf("Unique: %lu\n", areSame(elementsNumber, arr1, arr2));

    time_t method1Begin = time(NULL);
    insertionSort(elementsNumber, arr1);
    time_t method1End = time(NULL);

    time_t method2Begin = time(NULL);
    qsSort(arr2, 0, elementsNumber);
    time_t method2End = time(NULL);

    puts("\nAfter sorting");

    printf("Array1 is ordered: %d\n", arrayIsOrdered(elementsNumber, arr1));
    printf("Array2 is ordered: %d\n", arrayIsOrdered(elementsNumber, arr2));

    printf("Unique: %lu\n", areSame(elementsNumber, arr1, arr2));

    printf("\nMethod 1 took %ld seconds to execute\n", (method1End - method1Begin));
    printf("Method 2 took %ld seconds to execute\n", (method2End - method2Begin));

    return 0;
}

#include "sorting.h"

#include <stdlib.h>

static const DEFAULT_ELEMENTS_COUNT = 1e5;

void fillArray(int elementsCount, int *array[])
{
    for (int i = 0; i < elementsCount; i++)
    {
        *array[i] = rand();
    }
}

void insertionSort(int n, int mass[])
{
    int newElement, location;
 
    for (int i = 1; i < n; i++)
    {
        newElement = mass[i];
        location = i - 1;

        while(location >= 0 && mass[location] > newElement)
        {
            mass[location+1] = mass[location];
            location = location - 1;
        }
        
        mass[location+1] = newElement;
    }
}

int main(void)
{
    int arr1[], arr2[];

    fillArray(DEFAULT_ELEMENTS_COUNT, &arr1);
    fillArray(DEFAULT_ELEMENTS_COUNT, &arr2);

    return 0;
}
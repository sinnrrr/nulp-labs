#include <stdlib.h>
#include <time.h>

void fillArraysWithRandomItems(long size, long arr1[], long arr2[])
{
    srand(time(NULL));

    for (long i = 0; i < size; i++)
    {
        long randomNumber = rand();

        arr1[i] = randomNumber;
        arr2[i] = randomNumber;
    };
}

void cloneArray(const long size, long from[], long to[])
{
    for (long i = 0; i <= size; i++)
    {
        to[i] = from[i];
    }
}

long areSame(const long size, const long arr1[], const long arr2[])
{
    long sameItemsCount = 0;

    for (long i = 0; i < size; ++i)
    {
        if (arr1[i] == arr2[i])
            sameItemsCount++;
    }

    return sameItemsCount == size;
}

int arrayIsOrdered(const long size, const long arr[])
{
    for (long i = 1; i < size; ++i)
    {
        if (arr[i] < arr[i - 1])
            return 0;
    }

    return 1;
}

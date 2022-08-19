#include <stdio.h>
#include "../2/calculations.h"

int main(void)
{
    struct Record record = {-12.650, -2.255, 3.205};

    printf("Enter x and y values: ");
    scanf("%lf %lf", &record.x, &record.y);

    printf("Result: %lf", calculateWithFormula(record));

    return 0;
}

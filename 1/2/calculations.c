#include <math.h>
#include "calculations.h"

double calculateWithFormula(struct Record record)
{
    return pow(record.u, (record.x + record.y) / 2) - cbrt((record.x - 1) / ((fabs(record.y) + 1)));
}
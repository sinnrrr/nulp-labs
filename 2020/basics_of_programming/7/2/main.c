#include <math.h>
#include <stdio.h>

void tabulate(double x) {
    double y = pow(cos(x), 4);

    printf("% .10lf\t% .10lf\t\n", x, y);
}

void usingFor(double start, double step, double end) {
    for (double x = start; x < end; x += step) tabulate(x);
}

void usingWhile(double start, double step, double end) {
    double x = start;
    while (end > x) {
        tabulate(x);

        x += step;
    }
}

void usingDoWhile(double start, double step, double end) {
    double x = start;
    do {
        tabulate(x);

        x += step;
    } while (end > x);
}

int main(void) {
    void (*functions[])(
            double start,
            double step,
            double end
    ) = {&usingFor, &usingWhile, &usingDoWhile};

    double step, start, end;

    int methodToUse = 0;
    int methodsAvailableCount = sizeof functions / sizeof functions[0];

    printf("Enter start, step and the end: ");
    scanf("%lf %lf %lf", &start, &step, &end);

    printf("Enter method to use: ");
    scanf("%d", &methodToUse);

    if (methodToUse < 0 || methodToUse > methodsAvailableCount) {
        puts("We have any definition of that method number!");

        return 1;
    }

    functions[methodToUse](start, step, end);

    return 0;
}

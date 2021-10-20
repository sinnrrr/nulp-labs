#include <stdio.h>

struct Charges
{
    short sin, cos, tg, ctg;
};

char *getChargeChar(short charge)
{
    if (charge == 1)
    {
        return "positive";
    }
    else if (charge == -1)
    {
        return "negative";
    }

    return "no charge";
}

int main(void)
{
    double degree;
    struct Charges charges;

    printf("Enter degree value: ");
    scanf("%lf", &degree);

    if (degree < -360 || degree > 360)
    {
        puts("Must be in range of -360 and 360");

        return 1;
    }

    // // Substracting with remainder
    // while (degree <= -360 && degree >= 360)
    // {
    //     if (degree > 0)
    //     {
    //         degree = degree - 360;
    //     }
    //     else
    //     {
    //         degree = degree + 360;
    //     }
    // }

    // Making a period to have a positive degree
    if (degree < 0)
    {
        degree = 360 + degree;
    }

    printf("Degree after processing: %lf\n", degree);

    if (degree == 0)
    {
        charges.sin = 0;
        charges.cos = 1;
        charges.tg = 0;
        charges.ctg = 0;
    }
    else if (degree < 90)
    {
        charges.sin = 1;
        charges.cos = 1;
        charges.tg = 1;
        charges.ctg = 1;
    }
    else if (degree == 90)
    {
        charges.sin = 1;
        charges.cos = 0;
        charges.tg = 0;
        charges.ctg = 0;
    }
    else if (degree < 180)
    {
        charges.sin = 1;
        charges.cos = -1;
        charges.tg = -1;
        charges.ctg = -1;
    }
    else if (degree == 180)
    {
        charges.sin = 0;
        charges.cos = -1;
        charges.tg = 0;
        charges.ctg = 0;
    }
    else if (degree < 270)
    {
        charges.sin = -1;
        charges.cos = -1;
        charges.tg = 1;
        charges.ctg = 1;
    }
    else if (degree == 270)
    {
        charges.sin = -1;
        charges.cos = 0;
        charges.tg = 0;
        charges.ctg = 0;
    }
    else if (degree < 360)
    {
        charges.sin = -1;
        charges.cos = -1;
        charges.tg = 1;
        charges.ctg = 1;
    }

    printf("\nResults: \n");
    printf("sin: %s\n", getChargeChar(charges.sin));
    printf("cos: %s\n", getChargeChar(charges.cos));
    printf("tg: %s\n", getChargeChar(charges.tg));
    printf("ctg: %s\n", getChargeChar(charges.ctg));

    return 0;
}
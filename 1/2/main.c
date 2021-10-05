#include <stdio.h>

typedef enum
{
    true,
    false,
    null
} bool;

struct Charges
{
    bool sin, cos, tg, ctg;
};

char *get_charge_char(bool charge)
{
    if (charge)
    {
        return "positive";
    }
    else if (!charge)
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

    // Substracting with remainder
    while (degree <= -360 && degree >= 360)
    {
        if (degree > 0)
        {
            degree = degree - 360;
        }
        else
        {
            degree = degree + 360;
        }
    }

    // Making a period to have a positive degree
    if (degree < 0)
    {
        degree = 360 + degree;
    }

    printf("Degree after processing: %lf\n", degree);

    if (degree == 0)
    {
        charges.sin = null;
        charges.cos = true;
        charges.tg = null;
        charges.ctg = null;
    }
    else if (degree < 90)
    {
        charges.sin = true;
        charges.cos = true;
        charges.tg = true;
        charges.ctg = true;
    }
    else if (degree == 90)
    {
        charges.sin = true;
        charges.cos = null;
        charges.tg = null;
        charges.ctg = null;
    }
    else if (degree < 180)
    {
        charges.sin = true;
        charges.cos = false;
        charges.tg = false;
        charges.ctg = false;
    }
    else if (degree == 180)
    {
        charges.sin = null;
        charges.cos = false;
        charges.tg = null;
        charges.ctg = null;
    }
    else if (degree < 270)
    {
        charges.sin = false;
        charges.cos = false;
        charges.tg = true;
        charges.ctg = true;
    }
    else if (degree == 270)
    {
        charges.sin = false;
        charges.cos = null;
        charges.tg = null;
        charges.ctg = null;
    }
    else if (degree < 360)
    {
        charges.sin = false;
        charges.cos = false;
        charges.tg = true;
        charges.ctg = true;
    }

    printf("\nResults: \n");
    printf("sin: %s\n", get_charge_char(charges.sin));
    printf("cos: %s\n", get_charge_char(charges.cos));
    printf("tg: %s\n", get_charge_char(charges.tg));
    printf("ctg: %s\n", get_charge_char(charges.ctg));

    return 0;
}
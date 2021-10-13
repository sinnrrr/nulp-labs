// #include <stdio.h>
// #include <math.h>

// int main()
// {
//     double step, start, end;
//     double eps = 1E-200;

//     printf("Enter step, start and end of the line: ");
//     scanf("%lf %lf %lf", &step, &start, &end);

//     if(fabs(start) >= 1 || fabs(end) >= 1 || start > end || step > fabs(start - end))
//     {
//         printf("Valid bounds: (-1,1), don't make step too big!\n");
//         return 0;
//     }
//     double x = start;
//     while(x < end)
//     {
//         double formula = pow(1 + x, -3);
//         double result = 0;
//         double diff = 0;

//         int n = 0;
//         do
//         {
//             diff = 0.5*pow(x,n)*(pow(-1,n)*(1+n)*(2+n));
//             result += diff;
//             n++;
//         } while(fabs(diff) > eps); //do it until we have a nice precision

//         printf("x = % .1lf |\t\t", x);
//     	printf("formula = % .6lf |\t\t", formula);
//     	printf("taylor = % .6lf\n", result);
//     	printf("----------------------------------------------------------------------------\n");
//         x += step;
//     }

//     return 0;
// }

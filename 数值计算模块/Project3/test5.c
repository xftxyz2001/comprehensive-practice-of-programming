#include <stdio.h>
#include <math.h>

double f1(double x)
{
    return x / (1 + x * x);
}

double f2(double x)
{
    return 1 + x * x;
}

typedef double (*func)(double);

double central_difference(double x, double h, func f)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

int main(int argc, char const *argv[])
{
    double x = 1.0;
    double h = 1e-6;
    printf("f1'(1.0) = %.6f\n", central_difference(x, h, f1));
    printf("f2'(1.0) = %.6f\n", central_difference(x, h, f2));
    return 0;
}

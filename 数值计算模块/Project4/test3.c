#include <stdio.h>
#include <math.h>

typedef double (*func)(double);

// 二分法
double dhrt(double a, double b, double eps, int m, func f)
{
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0)
    {
        printf("Function has same signs at endpoints.\n");
        return -1; // Error value
    }
    for (int i = 0; i < m; i++)
    {
        double c = (a + b) / 2;
        double fc = f(c);
        if (fabs(fc) < eps || (b - a) / 2 < eps)
        {
            return c;
        }
        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }
    return (a + b) / 2;
}

// x^3 - 6x - 1 = 0
double f2(double x)
{
    return x * x * x - 6 * x - 1;
}
int main(int argc, char const *argv[])
{
    // Bisection method to find a real root of x^3 - 6x - 1 near x = 2
    double root3 = dhrt(1.0, 3.0, 1e-6, 1000, f2);
    printf("The root of the equation x^3 - 6x - 1 using bisection method is: %f\n", root3);

    return 0;
}

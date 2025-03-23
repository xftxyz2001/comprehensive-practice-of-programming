#include <stdio.h>
#include <math.h>

typedef double (*func)(double);

// 弦截法
double secant(double x0, double x1, double eps, int m, func f)
{
    double f0 = f(x0);
    double f1 = f(x1);
    for (int i = 0; i < m; i++)
    {
        if (fabs(f1) < eps)
        {
            return x1;
        }
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
    }
    return x1;
}

// x^3 - 2x^2 + 7x - 4 = 0
double f3(double x)
{
    return x * x * x - 2 * x * x + 7 * x - 4;
}

int main(int argc, char const *argv[])
{
    // Secant method to find a real root of x^3 - 2x^2 + 7x - 4 with an error not exceeding 10^-6
    double root4 = secant(0.0, 1.0, 1e-6, 1000, f3);
    printf("The root of the equation x^3 - 2x^2 + 7x - 4 using the secant method is: %f\n", root4);

    return 0;
}

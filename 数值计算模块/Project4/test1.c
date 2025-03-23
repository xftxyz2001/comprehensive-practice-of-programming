#include <stdio.h>
#include <math.h>

typedef double (*func)(double);

// 不动点迭代法
double dhrt2(double x0, double eps, int m, func g)
{
    double x = x0;
    for (int i = 0; i < m; i++)
    {
        double x_next = g(x);
        if (fabs(x_next - x) < eps)
        {
            return x_next;
        }
        x = x_next;
    }
    return x;
}

// x^3 + 2x^2 + 2x + 1 = 0
double g1(double x)
{
    return x * x * x + 2 * x * x + 2 * x + 1;
}

int main(int argc, char const *argv[])
{
    // Fixed-point iteration method to solve x^3 + 2x^2 + 2x + 1 = 0
    double root1 = dhrt2(0.0, 1e-6, 1000, g1);
    printf("The root of the equation x^3 + 2x^2 + 2x + 1 = 0 using fixed-point iteration method is: %f\n", root1);

    return 0;
}

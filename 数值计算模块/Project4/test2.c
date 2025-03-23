#include <stdio.h>
#include <math.h>

typedef double (*func)(double);

// 牛顿迭代法
double newt(double x0, double eps, int m, func f, func ff)
{
    double x = x0;
    for (int i = 0; i < m; i++)
    {
        double fx = f(x);
        double ffx = ff(x);
        if (fabs(fx) < eps)
        {
            return x;
        }
        x = x - fx / ffx;
    }
    return x;
}

// x^3 - 2x^2 + 4x + 1 = 0
double f1(double x)
{
    return x * x * x - 2 * x * x + 4 * x + 1;
}

double ff1(double x)
{
    return 3 * x * x - 4 * x + 4;
}

int main(int argc, char const *argv[])
{
    // Newton's method to find a real root of x^3 - 2x^2 + 4x + 1 near x = 0
    double root2 = newt(0.0, 1e-6, 1000, f1, ff1);
    printf("The root of the equation x^3 - 2x^2 + 4x + 1 using Newton's method is: %f\n", root2);

    return 0;
}

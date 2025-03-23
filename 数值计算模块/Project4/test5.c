#include <stdio.h>
#include <math.h>

typedef double (*func)(double);

// 黄金分割法
double gss(double a, double b, double eps, int m, func f)
{
    const double phi = (1 + sqrt(5)) / 2;
    double c = b - (b - a) / phi;
    double d = a + (b - a) / phi;
    for (int i = 0; i < m; i++)
    {
        if (fabs(b - a) < eps)
        {
            return (b + a) / 2;
        }
        if (f(c) < f(d))
        {
            b = d;
        }
        else
        {
            a = c;
        }
        c = b - (b - a) / phi;
        d = a + (b - a) / phi;
    }
    return (b + a) / 2;
}

// f(x) = x^2 - 4x + 4
double f4(double x)
{
    return x * x - 4 * x + 4;
}

int main(int argc, char const *argv[])
{
    // Golden section search method to find the minimum value of f(x) = x^2 - 4x + 4 in the interval [0, 4]
    double min_val = gss(0.0, 4.0, 1e-6, 1000, f4);
    printf("The minimum value of the function f(x) = x^2 - 4x + 4 in the interval [0, 4] using golden section search method is: %f\n", min_val);

    return 0;
}

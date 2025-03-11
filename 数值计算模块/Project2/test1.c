#include <stdio.h>
#include <math.h>

double lagrange_interpolation(double x[], double y[], int n, double xi)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        double li = 1.0;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                li *= (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += li * y[i];
    }
    return result;
}

int main(int argc, char *argv[])
{
    double x[3] = {1, 2, 3};
    double y[3] = {0.367879441, 0.135335283, 0.049787068};
    double xi = 2.6;
    printf("Lagrange interpolation at x = %lf: %lf\n", xi, lagrange_interpolation(x, y, 3, xi));
    return 0;
}

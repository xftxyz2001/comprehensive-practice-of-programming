#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define TOLERANCE 1e-6

double f1(double x)
{
    return x / (1 + x * x);
}

double f2(double x)
{
    return 1 + x * x;
}

typedef double (*func)(double);

// 计算勒让德多项式 P_n(x)
double legendre_polynomial(int n, double x)
{
    if (n == 0)
        return 1.0;
    if (n == 1)
        return x;

    double p0 = 1.0, p1 = x, pn;
    for (int k = 2; k <= n; k++)
    {
        pn = ((2 * k - 1) * x * p1 - (k - 1) * p0) / k;
        p0 = p1;
        p1 = pn;
    }
    return pn;
}

// 计算勒让德多项式的节点和权重
void legendre_nodes_weights(int n, double *nodes, double *weights)
{
    double x, x0, x1, dx, pn, pnm1, pnm2, pp;
    for (int i = 1; i <= n; i++)
    {
        x = cos(M_PI * (i - 0.25) / (n + 0.5));
        do
        {
            pnm1 = 1.0;
            pnm2 = 0.0;
            for (int j = 1; j <= n; j++)
            {
                pp = pnm1;
                pnm1 = ((2 * j - 1) * x * pnm1 - (j - 1) * pnm2) / j;
                pnm2 = pp;
            }
            dx = pnm1 - x * pnm2;
            x -= pnm1 / dx;
        } while (fabs(dx) > TOLERANCE);
        nodes[i - 1] = x;
        weights[i - 1] = 2.0 / ((1 - x * x) * dx * dx);
    }
}

// 高斯-勒让德积分法
double gauss_legendre(double (*f)(double), double a, double b, int n)
{
    // double nodes[n], weights[n];
    double *nodes = (double *)malloc(n * sizeof(double));
    double *weights = (double *)malloc(n * sizeof(double));
    legendre_nodes_weights(n, nodes, weights);

    double integral = 0.0;
    for (int i = 0; i < n; i++)
    {
        double xi = 0.5 * (b - a) * nodes[i] + 0.5 * (b + a);
        integral += weights[i] * f(xi);
    }
    integral *= 0.5 * (b - a);
    return integral;
}

int main(int argc, char const *argv[])
{
    double eps = 1e-7;
    // f1
    printf("f1:\n");
    printf("Gauss-Legendre method: %lf\n", gauss_legendre(0, 3, eps, f1));
    // f2
    printf("f2:\n");
    printf("Gauss-Legendre method: %lf\n", gauss_legendre(0, 2, eps, f2));
    return 0;
}
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

/**
 * 梯形法
 * @param a 区间左端点
 * @param b 区间右端点
 * @param n 划分的小区间数量
 * @return 积分结果
 */
double trapezoidal_method(double a, double b, int n, func f)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        double x_l = a + i * h;
        double x_r = a + (i + 1) * h;
        sum += (f(x_l) + f(x_r)) / 2 * h;
    }
    return sum;
}
int main(int argc, char const *argv[])
{
    int n = 1000;
    // f1
    printf("f1:\n");
    printf("Trapezoidal method: %lf\n", trapezoidal_method(0, 3, n, f1));
    // f2
    printf("f2:\n");
    printf("Trapezoidal method: %lf\n", trapezoidal_method(0, 2, n, f2));
    return 0;
}

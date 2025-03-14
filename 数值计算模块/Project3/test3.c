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
 * 辛普森法
 * @param a 区间左端点
 * @param b 区间右端点
 * @param n 划分的小区间数量
 * @return 积分结果
 */
double simpson_method(double a, double b, int n, func f)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        double fa = f(a + i * h);
        double fb = f(a + (i + 1) * h);
        double fm = f(a + (i + 0.5) * h);
        sum += (fa + 4 * fm + fb) * h / 6;
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int n = 1000;
    // f1
    printf("f1:\n");
    printf("Simpson method: %lf\n", simpson_method(0, 3, n, f1));
    // f2
    printf("f2:\n");
    printf("Simpson method: %lf\n", simpson_method(0, 2, n, f2));
    return 0;
}

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
 * 矩形法
 * @param a 区间左端点
 * @param b 区间右端点
 * @param n 划分的小区间数量
 * @param method 0: 左矩形法 1: 右矩形法
 * @return 积分结果
 */
double rectangle_method(double a, double b, int n, int method, func f)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        double x_l = a + i * h;
        double x_r = a + (i + 1) * h;
        switch (method)
        {
        case 0:
            sum += f(x_l) * h;
            break;
        case 1:
            sum += f(x_r) * h;
            break;
        default:
            printf("Invalid method!\n");
            return 0;
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int n = 1000;
    // f1
    printf("f1:\n");
    printf("Rectangle method (left): %lf\n", rectangle_method(0, 3, n, 0, f1));
    printf("Rectangle method (right): %lf\n", rectangle_method(0, 3, n, 1, f1));
    // f2
    printf("f2:\n");
    printf("Rectangle method (left): %lf\n", rectangle_method(0, 2, n, 0, f2));
    printf("Rectangle method (right): %lf\n", rectangle_method(0, 2, n, 1, f2));
    return 0;
}

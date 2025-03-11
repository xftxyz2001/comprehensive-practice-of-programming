#include <stdio.h>
#include <math.h>

// 定义样条插值函数
double cubicSplineInterpolation(double x, double x0, double x1, double x2, double x3, double y0, double y1, double y2, double y3)
{
    double a = (-y0 + 3 * y1 - 3 * y2 + y3) / 6;
    double b = (y0 - 2 * y1 + y2) / 2;
    double c = (-y0 + y2) / 2;
    double d = y1;
    return a * pow(x - x1, 3) + b * pow(x - x1, 2) + c * (x - x1) + d;
}

int main()
{
    // 给定的点和对应的函数值
    double x0 = 1, x1 = 2, x2 = 3;
    double y0 = exp(-x0), y1 = exp(-x1), y2 = exp(-x2);

    // 计算插值点
    double x = 2.6;
    double interpolatedValue = cubicSplineInterpolation(x, x0, x1, x2, x2 + 1, y0, y1, y2, exp(-(x2 + 1)));

    printf("The interpolated value of e^(-%f) is %f\n", x, interpolatedValue);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define A_ROWS 4
#define A_COLS 3
#define B_COLS 2

#define TOLERANCE 1e-6

void matrixMultiply(int A[A_ROWS][A_COLS], int B[A_COLS][B_COLS], int C[A_ROWS][B_COLS])
{
    for (int i = 0; i < A_ROWS; i++)
    {
        for (int j = 0; j < B_COLS; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < A_COLS; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int p1t1main(int argc, char *argv[])
{
    int A[A_ROWS][A_COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}};

    int B[A_COLS][B_COLS] = {
        {1, 2},
        {3, 4},
        {5, 6}};

    int C[A_ROWS][B_COLS]; // 保存结果

    matrixMultiply(A, B, C);

    printf("Matrix A:\n");
    for (int i = 0; i < A_ROWS; i++)
    {
        for (int j = 0; j < A_COLS; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < A_COLS; i++)
    {
        for (int j = 0; j < B_COLS; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < A_ROWS; i++)
    {
        for (int j = 0; j < B_COLS; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// ---
// 求最大公约数
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 求最小公倍数
int lcm(int a, int b)
{
    return abs(a * b) / gcd(a, b);
}

int p1t2main(int argc, char *argv[])
{
    int a = 36, b = 60;
    printf("GCD of %d and %d is %d\n", a, b, gcd(a, b));
    printf("LCM of %d and %d is %d\n", a, b, lcm(a, b));
    return 0;
}

// ---
void generalMatrixMultiply(int **A, int A_rows, int A_cols, int **B, int B_cols, int **C)
{
    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < B_cols; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < A_cols; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int **allocateMatrix(int rows, int cols)
{
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int p1t3main(int argc, char *argv[])
{
    int A_rows = 4, A_cols = 3, B_rows = 3, B_cols = 2;
    int **A = allocateMatrix(A_rows, A_cols);
    int **B = allocateMatrix(B_rows, B_cols);
    int **C = allocateMatrix(A_rows, B_cols);

    // 赋值
    int A_data[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}};
    int B_data[3][2] = {
        {13, 14},
        {15, 16},
        {17, 18}};

    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < A_cols; j++)
        {
            A[i][j] = A_data[i][j];
        }
    }

    for (int i = 0; i < B_rows; i++)
    {
        for (int j = 0; j < B_cols; j++)
        {
            B[i][j] = B_data[i][j];
        }
    }

    // 计算乘积
    generalMatrixMultiply(A, A_rows, A_cols, B, B_cols, C);

    // 打印结果
    printf("Result matrix C:\n");
    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < B_cols; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    freeMatrix(A, A_rows);
    freeMatrix(B, B_rows);
    freeMatrix(C, A_rows);

    return 0;
}

// ---
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

int p2t1main(int argc, char *argv[])
{
    double x[3] = {1, 2, 3};
    double y[3] = {0.367879441, 0.135335283, 0.049787068};
    double xi = 2.6;
    printf("Lagrange interpolation at x = %lf: %lf\n", xi, lagrange_interpolation(x, y, 3, xi));
    return 0;
}

// ---
// 建立分割差分表
void build_divided_difference_table(double x[], double y[], int n, double table[][4])
{
    for (int i = 0; i < n; i++)
    {
        table[i][0] = y[i];
    }
    for (int j = 1; j <= n - 1; j++)
    {
        for (int i = 0; i <= n - 1 - j; i++)
        {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// 计算Newton插值
double newton_interpolation(double x[], double table[][4], int n, double xi)
{
    double result = table[0][0];
    double product = 1.0;
    for (int i = 1; i < n; i++)
    {
        product *= (xi - x[i - 1]);
        result += table[0][i] * product;
    }
    return result;
}

int p2t2main(int argc, char const *argv[])
{
    double x[3] = {1, 2, 3};
    double y[3] = {0.367879441, 0.135335283, 0.049787068};
    double table[3][4];
    build_divided_difference_table(x, y, 3, table);
    double xi = 2.6;
    printf("Newton interpolation at x = %lf: %lf\n", xi, newton_interpolation(x, table, 3, xi));
    return 0;
}

// ---
// 定义样条插值函数
double cubicSplineInterpolation(double x, double x0, double x1, double x2, double x3, double y0, double y1, double y2, double y3)
{
    double a = (-y0 + 3 * y1 - 3 * y2 + y3) / 6;
    double b = (y0 - 2 * y1 + y2) / 2;
    double c = (-y0 + y2) / 2;
    double d = y1;
    return a * pow(x - x1, 3) + b * pow(x - x1, 2) + c * (x - x1) + d;
}

int p2t4main(int argc, char const *argv[])
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

// ---
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

int p3t1main(int argc, char const *argv[])
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

// ---
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
int p3t2main(int argc, char const *argv[])
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

// ---
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

int p3t3main(int argc, char const *argv[])
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

// ---
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

int p3t4main(int argc, char const *argv[])
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

// ---
double central_difference(double x, double h, func f)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

int p3t5main(int argc, char const *argv[])
{
    double x = 1.0;
    double h = 1e-6;
    printf("f1'(1.0) = %.6f\n", central_difference(x, h, f1));
    printf("f2'(1.0) = %.6f\n", central_difference(x, h, f2));
    return 0;
}

// ---
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

int p4t1main(int argc, char const *argv[])
{
    // Fixed-point iteration method to solve x^3 + 2x^2 + 2x + 1 = 0
    double root1 = dhrt2(0.0, 1e-6, 1000, g1);
    printf("The root of the equation x^3 + 2x^2 + 2x + 1 = 0 using fixed-point iteration method is: %f\n", root1);

    return 0;
}

// ---
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

int p4t2main(int argc, char const *argv[])
{
    // Newton's method to find a real root of x^3 - 2x^2 + 4x + 1 near x = 0
    double root2 = newt(0.0, 1e-6, 1000, f1, ff1);
    printf("The root of the equation x^3 - 2x^2 + 4x + 1 using Newton's method is: %f\n", root2);

    return 0;
}

// ---
// 二分法
double dhrt(double a, double b, double eps, int m, func f)
{
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0)
    {
        printf("Function has same signs at endpoints.\n");
        return -1; // Error value
    }
    for (int i = 0; i < m; i++)
    {
        double c = (a + b) / 2;
        double fc = f(c);
        if (fabs(fc) < eps || (b - a) / 2 < eps)
        {
            return c;
        }
        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }
    return (a + b) / 2;
}

// x^3 - 6x - 1 = 0
double f2(double x)
{
    return x * x * x - 6 * x - 1;
}
int p4t3main(int argc, char const *argv[])
{
    // Bisection method to find a real root of x^3 - 6x - 1 near x = 2
    double root3 = dhrt(1.0, 3.0, 1e-6, 1000, f2);
    printf("The root of the equation x^3 - 6x - 1 using bisection method is: %f\n", root3);

    return 0;
}

// ---
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

int p4t4main(int argc, char const *argv[])
{
    // Secant method to find a real root of x^3 - 2x^2 + 7x - 4 with an error not exceeding 10^-6
    double root4 = secant(0.0, 1.0, 1e-6, 1000, f3);
    printf("The root of the equation x^3 - 2x^2 + 7x - 4 using the secant method is: %f\n", root4);

    return 0;
}

// ---
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

int p5t5main(int argc, char const *argv[])
{
    // Golden section search method to find the minimum value of f(x) = x^2 - 4x + 4 in the interval [0, 4]
    double min_val = gss(0.0, 4.0, 1e-6, 1000, f4);
    printf("The minimum value of the function f(x) = x^2 - 4x + 4 in the interval [0, 4] using golden section search method is: %f\n", min_val);

    return 0;
}

int main(int argc, char const *argv[])
{
    while (1)
    {
        printf("Please input the number of the test case:\n");
        printf("1. matrix multiply\n");
        printf("2. gcd and lcm\n");
        printf("3. lagrange interpolation\n");
        printf("4. newton interpolation\n");
        printf("5. cubic spline interpolation\n");
        printf("6. rectangle method\n");
        printf("7. trapezoidal method\n");
        printf("8. simpson method\n");
        printf("9. gauss-legendre method\n");
        printf("10. central difference\n");
        printf("11. fixed-point iteration method\n");
        printf("12. Newton's method\n");
        printf("13. bisection method\n");
        printf("14. secant method\n");
        printf("15. golden section search method\n");
        printf("0. exit\n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            p1t1main(argc, argv);
            break;
        case 2:
            p1t2main(argc, argv);
            break;
        case 3:
            p2t1main(argc, argv);
            break;
        case 4:
            p2t2main(argc, argv);
            break;
        case 5:
            p2t4main(argc, argv);
            break;
        case 6:
            p3t1main(argc, argv);
            break;
        case 7:
            p3t2main(argc, argv);
            break;
        case 8:
            p3t3main(argc, argv);
            break;
        case 9:
            p3t4main(argc, argv);
            break;
        case 10:
            p3t5main(argc, argv);
            break;
        case 11:
            p4t1main(argc, argv);
            break;
        case 12:
            p4t2main(argc, argv);
            break;
        case 13:
            p4t3main(argc, argv);
            break;
        case 14:
            p4t4main(argc, argv);
            break;
        case 15:
            p5t5main(argc, argv);
            break;

        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    return 0;
}

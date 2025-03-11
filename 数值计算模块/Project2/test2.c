#include <stdio.h>
#include <math.h>

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

int main(int argc, char const *argv[])
{
    double x[3] = {1, 2, 3};
    double y[3] = {0.367879441, 0.135335283, 0.049787068};
    double table[3][4];
    build_divided_difference_table(x, y, 3, table);
    double xi = 2.6;
    printf("Newton interpolation at x = %lf: %lf\n", xi, newton_interpolation(x, table, 3, xi));
    return 0;
}

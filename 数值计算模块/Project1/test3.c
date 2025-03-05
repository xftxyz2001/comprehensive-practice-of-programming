#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
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
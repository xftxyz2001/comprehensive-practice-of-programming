#include <stdio.h>

#define A_ROWS 4
#define A_COLS 3
#define B_COLS 2

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

int main(int argc, char *argv[])
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
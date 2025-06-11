// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "square.h"
#include "sqrt.h"

int main(int argc, char const *argv[])
{
    int num;

    printf("请输入一个整数: ");
    scanf("%d", &num);

    printf("平方: %d\n", square(num));
    printf("开方: %.2f\n", compute_sqrt(num));

    return 0;
}

// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "square.h"
#include "sqrt.h"

int main(int argc, char const *argv[])
{
    int num;

    printf("������һ������: ");
    scanf("%d", &num);

    printf("ƽ��: %d\n", square(num));
    printf("����: %.2f\n", compute_sqrt(num));

    return 0;
}

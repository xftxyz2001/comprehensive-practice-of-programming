// main.c - ������
#include <stdio.h>   // ��׼�������ͷ�ļ�
#include "square.h"
#include "sqrt.h"

int main(void) {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);  // ��ȡ�û����������

    // ���ú�����������
    printf("Square: %d\n", square(num));
    printf("Square Root: %.2f\n", square_root(num));

    return 0;
}

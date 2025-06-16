// main.c - 主程序
#include <stdio.h>   // 标准输入输出头文件
#include "square.h"
#include "sqrt.h"

int main(void) {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);  // 读取用户输入的整数

    // 调用函数并输出结果
    printf("Square: %d\n", square(num));
    printf("Square Root: %.2f\n", square_root(num));

    return 0;
}

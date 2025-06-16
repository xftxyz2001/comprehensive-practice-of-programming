// sqrt.c - 平方根函数实现
#include "sqrt.h"

// 计算x的平方根（需转换为double类型）
double square_root(int x) {
    return sqrt((double)x);  // C语言的sqrt参数需为double
}

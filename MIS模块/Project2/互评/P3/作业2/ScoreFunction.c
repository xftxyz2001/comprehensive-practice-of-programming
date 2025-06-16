#include <stdio.h>
#include "ScoreFunction.h"

int nPassScore = 60; // 全局及格线（文件作用域）

int CalFailNo(Student arr[], int num, int subject, const char* filename) {
    int nPassScore = 50; // 局部变量（函数作用域，覆盖全局变量）
    int counter = 0;
    FILE *fp = fopen(filename, "w");
    
    if (!fp) return -1; // 文件打开失败
    int i;
    for (i = 0; i < num; i++) {
        /* 实际生效的是局部变量50，因为：
           1. 局部变量与全局变量同名时，局部变量优先
           2. 此处作用域内最近的定义是函数内的nPassScore */
        if (arr[i].scores[subject] < nPassScore) { 
            fprintf(fp, "%04d %-10s %.2f\n", 
                    arr[i].id, 
                    arr[i].name, 
                    arr[i].scores[subject]);
            counter++;
        }
    }
    
    fclose(fp);
    return counter; // 返回不及格人数
}

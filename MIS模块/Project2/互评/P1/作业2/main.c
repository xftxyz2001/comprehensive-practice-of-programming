// main.c - 主程序
#include <stdio.h>
#include <stdlib.h>
#include "ScoreFunction.h"

int main() {
    Student students[STUDENT_NUM];
    FILE *infile = fopen("student.txt", "r");
    int i, j;  // 提前声明循环变量

    if (infile == NULL) {
        perror("Error opening student.txt");
        return EXIT_FAILURE;
    }

    // 读取学生数据
    for (i = 0; i < STUDENT_NUM; i++) {
        fscanf(infile, "%d %10s", &students[i].id, students[i].name);
        for (j = 0; j < 3; j++) {
            fscanf(infile, "%f", &students[i].scores[j]);
        }
    }
    fclose(infile);

    // 计算第0门课程（示例）的不及格人数
    int fails = CalFailNo(students, STUDENT_NUM, 0, "math_fail.txt");
    printf("Math fails: %d\n", fails);

    return 0;
}

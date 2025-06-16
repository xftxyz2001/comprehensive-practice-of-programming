// ScoreFunction.c - 学生成绩处理实现
#include <stdio.h>
#include <stdlib.h>
#include "ScoreFunction.h"

int nPassScore = 60;  // 全局变量（及格线）

int CalFailNo(Student students[], int num, int subject, const char* filename) {
    int nPassScore = 50;  // 局部变量（覆盖全局变量）
    int count = 0;
    FILE *outfile = fopen(filename, "w");
    int i;  // 提前声明循环变量

    if (outfile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < num; i++) {
        // 使用局部变量nPassScore=50进行判断
        if (students[i].scores[subject] < nPassScore) {
            fprintf(outfile, "%d %s %.2f\n", 
                    students[i].id, 
                    students[i].name, 
                    students[i].scores[subject]);
            count++;
        }
    }

    fclose(outfile);
    return count;
}

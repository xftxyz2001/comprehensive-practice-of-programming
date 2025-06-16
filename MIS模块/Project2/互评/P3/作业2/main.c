#include <stdio.h>
#include "ScoreFunction.h"

// 从文件中读取学生信息
void ReadStudents(Student students[], const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    int i;
    for (i = 0; i < STUDENT_NUM; i++) {
        fscanf(fp, "%d %10s %f %f %f",
               &students[i].id,
               students[i].name,
               &students[i].scores[0],
               &students[i].scores[1],
               &students[i].scores[2]);
    }
    fclose(fp);
}

int main() {
    Student students[STUDENT_NUM];

    // 读取数据
    ReadStudents(students, "student.txt");

    // 检查数学成绩（假设subject=0是数学）
    int fails = CalFailNo(students, STUDENT_NUM, 0, "math_fails.txt");
    printf("不及格人数：%d （实际使用及格线：50）\n", fails);

    return 0;
}

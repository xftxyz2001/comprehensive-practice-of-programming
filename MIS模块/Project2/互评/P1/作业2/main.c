// main.c - ������
#include <stdio.h>
#include <stdlib.h>
#include "ScoreFunction.h"

int main() {
    Student students[STUDENT_NUM];
    FILE *infile = fopen("student.txt", "r");
    int i, j;  // ��ǰ����ѭ������

    if (infile == NULL) {
        perror("Error opening student.txt");
        return EXIT_FAILURE;
    }

    // ��ȡѧ������
    for (i = 0; i < STUDENT_NUM; i++) {
        fscanf(infile, "%d %10s", &students[i].id, students[i].name);
        for (j = 0; j < 3; j++) {
            fscanf(infile, "%f", &students[i].scores[j]);
        }
    }
    fclose(infile);

    // �����0�ſγ̣�ʾ�����Ĳ���������
    int fails = CalFailNo(students, STUDENT_NUM, 0, "math_fail.txt");
    printf("Math fails: %d\n", fails);

    return 0;
}

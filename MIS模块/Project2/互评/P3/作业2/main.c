#include <stdio.h>
#include "ScoreFunction.h"

// ���ļ��ж�ȡѧ����Ϣ
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

    // ��ȡ����
    ReadStudents(students, "student.txt");

    // �����ѧ�ɼ�������subject=0����ѧ��
    int fails = CalFailNo(students, STUDENT_NUM, 0, "math_fails.txt");
    printf("������������%d ��ʵ��ʹ�ü����ߣ�50��\n", fails);

    return 0;
}

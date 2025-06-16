#include <stdio.h>
#include "ScoreFunction.h"

int main() {
    Student students[STUDENT_NUM];
    FILE *fp = fopen("student.txt", "r");
    if (!fp) return -1;
    for (int i = 0; i < STUDENT_NUM; i++) {
        fscanf(fp, "%d %s %f %f %f", &students[i].id, students[i].name, 
              &students[i].scores[0], &students[i].scores[1], &students[i].scores[2]);
    }
    fclose(fp);

    for (int subj = 0; subj < 3; subj++) {
        char filename[20];
        sprintf(filename, "fail_course%d.txt", subj + 1);
        int fails = CalFailNo(students, STUDENT_NUM, subj, filename);
        printf("Course %d: %d students failed.\n", subj + 1, fails);
    }
    return 0;
}

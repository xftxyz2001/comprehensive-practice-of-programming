// ScoreFunction.c - ѧ���ɼ�����ʵ��
#include <stdio.h>
#include <stdlib.h>
#include "ScoreFunction.h"

int nPassScore = 60;  // ȫ�ֱ����������ߣ�

int CalFailNo(Student students[], int num, int subject, const char* filename) {
    int nPassScore = 50;  // �ֲ�����������ȫ�ֱ�����
    int count = 0;
    FILE *outfile = fopen(filename, "w");
    int i;  // ��ǰ����ѭ������

    if (outfile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < num; i++) {
        // ʹ�þֲ�����nPassScore=50�����ж�
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

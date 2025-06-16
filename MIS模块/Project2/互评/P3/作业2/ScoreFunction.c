#include <stdio.h>
#include "ScoreFunction.h"

int nPassScore = 60; // ȫ�ּ����ߣ��ļ�������

int CalFailNo(Student arr[], int num, int subject, const char* filename) {
    int nPassScore = 50; // �ֲ����������������򣬸���ȫ�ֱ�����
    int counter = 0;
    FILE *fp = fopen(filename, "w");
    
    if (!fp) return -1; // �ļ���ʧ��
    int i;
    for (i = 0; i < num; i++) {
        /* ʵ����Ч���Ǿֲ�����50����Ϊ��
           1. �ֲ�������ȫ�ֱ���ͬ��ʱ���ֲ���������
           2. �˴�������������Ķ����Ǻ����ڵ�nPassScore */
        if (arr[i].scores[subject] < nPassScore) { 
            fprintf(fp, "%04d %-10s %.2f\n", 
                    arr[i].id, 
                    arr[i].name, 
                    arr[i].scores[subject]);
            counter++;
        }
    }
    
    fclose(fp);
    return counter; // ���ز���������
}

#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#define STUDENT_NUM 10  // �궨��ѧ������

// ѧ����Ϣ�ṹ�壨�������뱣����
typedef struct {
    int id;            // 4λ����ѧ��
    char name[11];     // ����(10�ַ�+1������)
    float scores[3];   // ���ſγɼ�����
} Student;

// ��������
int CalFailNo(Student arr[], int num, int subject, const char* filename);

#endif

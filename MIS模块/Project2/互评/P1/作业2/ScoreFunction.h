// ScoreFunction.h - ѧ���ɼ�����ͷ�ļ�
#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#define STUDENT_NUM 10    // �궨��ѧ������

// �������붨��ṹ��
#ifndef STUDENT_STRUCT
#define STUDENT_STRUCT
typedef struct {
    int id;               // ѧ�ţ�4λ������
    char name[11];        // ������������10�ַ���
    float scores[3];      // 3�ſγɼ�������2λС����
} Student;
#endif

// ����������ͳ�Ʋ�����������������
int CalFailNo(Student students[], int num, int subject, const char* filename);

#endif

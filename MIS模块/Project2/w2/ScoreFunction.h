// ScoreFunction.h
#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#include <string>
using namespace std;

#define MAX_STUDENTS 10

// �������붨��ѧ���ṹ��
#ifndef STUDENT_STRUCT_DEFINED
#define STUDENT_STRUCT_DEFINED

struct Student
{
    int id;          // ѧ�ţ�4λ������
    char name[11];   // ������������10���ַ���+1 ���� '\0'��
    float scores[3]; // ���ſγɼ�
};

#endif

// ��������
void readStudents(const char *filename, Student stu[], int &count);
int CalFailNo(Student stu[], int count, int subjectIndex, const char *outFilename);

#endif

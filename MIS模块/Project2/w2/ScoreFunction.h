// ScoreFunction.h
#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#include <string>
using namespace std;

#define MAX_STUDENTS 10

// 条件编译定义学生结构体
#ifndef STUDENT_STRUCT_DEFINED
#define STUDENT_STRUCT_DEFINED

struct Student
{
    int id;          // 学号（4位整数）
    char name[11];   // 姓名（不超过10个字符，+1 用于 '\0'）
    float scores[3]; // 三门课成绩
};

#endif

// 函数声明
void readStudents(const char *filename, Student stu[], int &count);
int CalFailNo(Student stu[], int count, int subjectIndex, const char *outFilename);

#endif

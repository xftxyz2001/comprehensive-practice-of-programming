#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#define STUDENT_NUM 10  // 宏定义学生人数

// 学生信息结构体（条件编译保护）
typedef struct {
    int id;            // 4位数字学号
    char name[11];     // 姓名(10字符+1结束符)
    float scores[3];   // 三门课成绩数组
} Student;

// 函数声明
int CalFailNo(Student arr[], int num, int subject, const char* filename);

#endif

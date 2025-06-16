// ScoreFunction.h - 学生成绩处理头文件
#ifndef SCORE_FUNCTION_H
#define SCORE_FUNCTION_H

#define STUDENT_NUM 10    // 宏定义学生人数

// 条件编译定义结构体
#ifndef STUDENT_STRUCT
#define STUDENT_STRUCT
typedef struct {
    int id;               // 学号（4位整数）
    char name[11];        // 姓名（不超过10字符）
    float scores[3];      // 3门课成绩（保留2位小数）
} Student;
#endif

// 函数声明：统计不及格人数并保存结果
int CalFailNo(Student students[], int num, int subject, const char* filename);

#endif

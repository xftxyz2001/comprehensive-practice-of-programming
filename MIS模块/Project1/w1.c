#include <stdio.h>

#define MAX 10

typedef struct
{
    int id;        // 学号（4位整数）
    char name[11]; // 姓名（不超过10个字符）
    float score1;
    float score2;
    float score3;
} Student;

int main(int argc, char const *argv[])
{
    int n;
    Student students[MAX];

    // 输入学生人数
    scanf("%d", &n);

    // 输入学生信息
    for (int i = 0; i < n; i++)
    {
        scanf("%d %s %f %f %f",
              &students[i].id,
              students[i].name,
              &students[i].score1,
              &students[i].score2,
              &students[i].score3);
    }

    // 打开文件写入
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        printf("无法打开文件！\n");
        return 1;
    }

    // 写入并输出标题
    fprintf(fp, "NO. Name Score1 Score2 Score3\n");
    printf("NO. Name Score1 Score2 Score3\n");

    // 写入数据并输出到屏幕
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %.2f %.2f %.2f\n",
                students[i].id,
                students[i].name,
                students[i].score1,
                students[i].score2,
                students[i].score3);

        printf("%d %s %.2f %.2f %.2f\n",
               students[i].id,
               students[i].name,
               students[i].score1,
               students[i].score2,
               students[i].score3);
    }

    fclose(fp); // 关闭文件

    return 0;
}

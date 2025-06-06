#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20 // 最多学生数（原本最多10个，加1个新输入）

typedef struct
{
    int id;        // 学号（4位整数）
    char name[11]; // 姓名（不超过10字符）
    float score1;
    float score2;
    float score3;
} Student;

int main()
{
    Student students[MAX];
    int count = 0;

    // 打开原文件 student.txt 读取
    FILE *fp_in = fopen("student.txt", "r");
    if (fp_in == NULL)
    {
        printf("无法打开 student.txt 文件！\n");
        return 1;
    }

    char header[50];
    fgets(header, sizeof(header), fp_in); // 跳过标题行

    // 读取学生数据
    while (fscanf(fp_in, "%d %s %f %f %f",
                  &students[count].id,
                  students[count].name,
                  &students[count].score1,
                  &students[count].score2,
                  &students[count].score3) == 5)
    {
        count++;
    }

    fclose(fp_in); // 关闭读取文件

    // 输入一个新学生的信息
    Student newStudent;
    scanf("%d %s %f %f %f",
          &newStudent.id,
          newStudent.name,
          &newStudent.score1,
          &newStudent.score2,
          &newStudent.score3);

    students[count] = newStudent;
    count++;

    // 打开新文件 student_new.txt 写入
    FILE *fp_out = fopen("student_new.txt", "w");
    if (fp_out == NULL)
    {
        printf("无法创建 student_new.txt 文件！\n");
        return 1;
    }

    // 写入并输出标题
    fprintf(fp_out, "NO. Name Score1 Score2 Score3\n");
    printf("NO. Name Score1 Score2 Score3\n");

    // 写入所有学生数据到文件，并显示到屏幕
    for (int i = 0; i < count; i++)
    {
        fprintf(fp_out, "%d %s %.2f %.2f %.2f\n",
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

    fclose(fp_out); // 关闭写入文件

    return 0;
}

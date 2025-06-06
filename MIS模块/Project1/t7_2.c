#include <stdio.h>

#define MAX 10

typedef struct
{
    char id[6];    // 学号：5位数字 + '\0'
    char name[10]; // 姓名：长度 < 10
    int score1;
    int score2;
    int score3;
    int total; // 总分
} Student;

int main(int argc, char const *argv[])
{
    int n;
    Student students[MAX];

    scanf("%d", &n);

    int maxIndex = 0;
    int maxTotal = -1;

    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %d %d %d",
              students[i].id,
              students[i].name,
              &students[i].score1,
              &students[i].score2,
              &students[i].score3);

        students[i].total = students[i].score1 + students[i].score2 + students[i].score3;

        if (students[i].total > maxTotal)
        {
            maxTotal = students[i].total;
            maxIndex = i;
        }
    }

    // 输出总分最高的学生
    printf("%s %s %d\n",
           students[maxIndex].name,
           students[maxIndex].id,
           students[maxIndex].total);

    return 0;
}

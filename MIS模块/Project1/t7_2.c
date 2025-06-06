#include <stdio.h>

#define MAX 10

typedef struct
{
    char id[6];    // ѧ�ţ�5λ���� + '\0'
    char name[10]; // ���������� < 10
    int score1;
    int score2;
    int score3;
    int total; // �ܷ�
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

    // ����ܷ���ߵ�ѧ��
    printf("%s %s %d\n",
           students[maxIndex].name,
           students[maxIndex].id,
           students[maxIndex].total);

    return 0;
}

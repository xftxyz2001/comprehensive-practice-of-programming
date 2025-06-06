#include <stdio.h>

#define MAX 10

typedef struct
{
    int id;        // ѧ�ţ�4λ������
    char name[11]; // ������������10���ַ���
    float score1;
    float score2;
    float score3;
} Student;

int main(int argc, char const *argv[])
{
    int n;
    Student students[MAX];

    // ����ѧ������
    scanf("%d", &n);

    // ����ѧ����Ϣ
    for (int i = 0; i < n; i++)
    {
        scanf("%d %s %f %f %f",
              &students[i].id,
              students[i].name,
              &students[i].score1,
              &students[i].score2,
              &students[i].score3);
    }

    // ���ļ�д��
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        printf("�޷����ļ���\n");
        return 1;
    }

    // д�벢�������
    fprintf(fp, "NO. Name Score1 Score2 Score3\n");
    printf("NO. Name Score1 Score2 Score3\n");

    // д�����ݲ��������Ļ
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

    fclose(fp); // �ر��ļ�

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20 // ���ѧ������ԭ�����10������1�������룩

typedef struct
{
    int id;        // ѧ�ţ�4λ������
    char name[11]; // ������������10�ַ���
    float score1;
    float score2;
    float score3;
} Student;

int main()
{
    Student students[MAX];
    int count = 0;

    // ��ԭ�ļ� student.txt ��ȡ
    FILE *fp_in = fopen("student.txt", "r");
    if (fp_in == NULL)
    {
        printf("�޷��� student.txt �ļ���\n");
        return 1;
    }

    char header[50];
    fgets(header, sizeof(header), fp_in); // ����������

    // ��ȡѧ������
    while (fscanf(fp_in, "%d %s %f %f %f",
                  &students[count].id,
                  students[count].name,
                  &students[count].score1,
                  &students[count].score2,
                  &students[count].score3) == 5)
    {
        count++;
    }

    fclose(fp_in); // �رն�ȡ�ļ�

    // ����һ����ѧ������Ϣ
    Student newStudent;
    scanf("%d %s %f %f %f",
          &newStudent.id,
          newStudent.name,
          &newStudent.score1,
          &newStudent.score2,
          &newStudent.score3);

    students[count] = newStudent;
    count++;

    // �����ļ� student_new.txt д��
    FILE *fp_out = fopen("student_new.txt", "w");
    if (fp_out == NULL)
    {
        printf("�޷����� student_new.txt �ļ���\n");
        return 1;
    }

    // д�벢�������
    fprintf(fp_out, "NO. Name Score1 Score2 Score3\n");
    printf("NO. Name Score1 Score2 Score3\n");

    // д������ѧ�����ݵ��ļ�������ʾ����Ļ
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

    fclose(fp_out); // �ر�д���ļ�

    return 0;
}

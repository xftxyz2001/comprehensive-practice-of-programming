#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct
{
    char name[11];    // �������10���ַ�+1��'\0'
    char birthday[9]; // ���գ�8λ�ַ���yyyymmdd + '\0'
    char phone[18];   // �绰���17λ�ַ�+1��'\0'
} Friend;

int compare(const void *a, const void *b)
{
    // �����մ�С���������������ǰ��
    return strcmp(((Friend *)a)->birthday, ((Friend *)b)->birthday);
}

int main(int argc, char const *argv[])
{
    int n;
    Friend friends[MAX];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %s", friends[i].name, friends[i].birthday, friends[i].phone);
    }

    // ʹ�ñ�׼�⺯��qsort����
    qsort(friends, n, sizeof(Friend), compare);

    // ������Ӵ�С���
    for (int i = 0; i < n; i++)
    {
        printf("%s %s %s\n", friends[i].name, friends[i].birthday, friends[i].phone);
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct
{
    char name[11];    // 姓名：最长10个字符+1个'\0'
    char birthday[9]; // 生日：8位字符串yyyymmdd + '\0'
    char phone[18];   // 电话：最长17位字符+1个'\0'
} Friend;

int compare(const void *a, const void *b)
{
    // 按生日从小到大排序（年龄大在前）
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

    // 使用标准库函数qsort排序
    qsort(friends, n, sizeof(Friend), compare);

    // 按年龄从大到小输出
    for (int i = 0; i < n; i++)
    {
        printf("%s %s %s\n", friends[i].name, friends[i].birthday, friends[i].phone);
    }

    return 0;
}

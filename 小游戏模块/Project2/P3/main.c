#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int a = 2000,b=2000;
    int p,sz,i,guess,sum=0,pt,lastpt;
    srand(time(NULL));
    printf("��������:");
    scanf("%d",&sz);
    while(a>0 && b>0)
    {
        sum=0;
        printf("�����뱾��Ͷע��:");
        scanf("%d",&p);
        printf("���(1)С��(2)�����(3)����:");  //�˴�����1��2������3
        scanf("%d",&guess);
        for(i=0;i<sz;i++)
        {
            pt = rand()%6+1;
            sum+=pt;
            if(i==0)
                lastpt = pt;
            else if(lastpt != pt)
                lastpt = 0;
        }
        if(guess == 3 && lastpt != 0)
        {
            printf("��ϲ��������Ϊ���ӣ���Ӯ��!");
            a -= 5*p;
            b += 5*p;
            printf("��ǰ���Ļ���Ϊ:%d�����Ի���Ϊ:%d\n",a,b);
        }
        else if(lastpt != 0)
        {
            printf("���ź�������Ϊ���ӣ�������!");
            a += 5*p;
            b -= 5*p;
            printf("��ǰ���Ļ���Ϊ:%d�����Ի���Ϊ:%d\n",a,b);
        }
        else if((guess == 1 && sum <= 3*sz) || (guess==2 && sum > 3*sz))
        {
            printf("��ϲ�������ֵ�����:%d����Ӯ�ˣ�",sum);
            a += p;
            b -= p;
            printf("��ǰ���Ļ���Ϊ:%d�����Ի���Ϊ:%d\n",a,b);
        }
        else
        {
            printf("���ź������ֵ�����:%d�������ˣ�",sum);
            a -= p;
            b += p;
            printf("��ǰ���Ļ���Ϊ:%d�����Ի���Ϊ:%d\n",a,b);
        }
    }
    if(a>0)
        printf("��ϲ��Ӯ��!\n");
    else
        printf("���ź�������Ӯ��!\n");
    return 0;
}
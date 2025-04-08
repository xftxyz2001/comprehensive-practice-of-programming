#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int a = 2000,b=2000;
    int p,sz,i,guess,sum=0,pt,lastpt;
    srand(time(NULL));
    printf("骰子数量:");
    scanf("%d",&sz);
    while(a>0 && b>0)
    {
        sum=0;
        printf("请输入本次投注额:");
        scanf("%d",&p);
        printf("请猜(1)小、(2)大或者(3)豹子:");  //此处输入1，2，或者3
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
            printf("恭喜您，本局为豹子，您赢了!");
            a -= 5*p;
            b += 5*p;
            printf("当前您的积分为:%d，电脑积分为:%d\n",a,b);
        }
        else if(lastpt != 0)
        {
            printf("很遗憾，本局为豹子，您输了!");
            a += 5*p;
            b -= 5*p;
            printf("当前您的积分为:%d，电脑积分为:%d\n",a,b);
        }
        else if((guess == 1 && sum <= 3*sz) || (guess==2 && sum > 3*sz))
        {
            printf("恭喜您，本局点数是:%d，您赢了！",sum);
            a += p;
            b -= p;
            printf("当前您的积分为:%d，电脑积分为:%d\n",a,b);
        }
        else
        {
            printf("很遗憾，本局点数是:%d，您输了！",sum);
            a -= p;
            b += p;
            printf("当前您的积分为:%d，电脑积分为:%d\n",a,b);
        }
    }
    if(a>0)
        printf("恭喜您赢了!\n");
    else
        printf("很遗憾，电脑赢了!\n");
    return 0;
}
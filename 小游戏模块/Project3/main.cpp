/*头文件声明开始*/
#include <stdio.h>   //包含标准输入输出库
#include <stdlib.h>  //包含标准库函数
#include <windows.h> //包含定义了关于创建窗口，消息循环等函数，如果要用API来做有界面的程序的话，必须要用到这个头文件；
#include <time.h>    //包含日期和时间的头文件，用于需要时间方面的函数 ；
#include <math.h>    //包含了很多数学方法的函数库
/*头文件声明结束*/

/*函数声明开始*/

void MainMenu();     // 菜单页面模块
void PlayerChoice(); // 选项模块
void ExitGame();     // 退出模块
void Magician();     // 魔术师功能模块
void Viewer();       // 观众模块
// int  InputFiveNumber();                            //输入5个数的值
/*函数声明结束*/

/*定义全局变量开始*/
int nHundreds; // 百位
int nTens;     // 十位
int nOnes;     // 个位
int nSum;      // 计算的 5个数的和值
int nNumber;   // 三位数的值
/*定义全局变量结束*/

int main()
{
    MainMenu(); // 调用主菜单函数
    return 0;
}

void MainMenu() // 系统主菜单
{

    int nSelect1; // 局部变量表示选项
    while (1)
    {
        printf("-------------------------------Main Menu-------------------------------\n");
        printf("\n");
        printf("\t     1   退出\n");
        printf("\t     2   进入游戏\n");
        printf("请输入相应的数字，进入不同的模块:  \n");
        printf("-----------------------------------------------------------------------\n");
        scanf("%d", &nSelect1);
        getchar();
        fflush(stdin);
        if (nSelect1 == 1)
        {
            ExitGame(); // 跳转到退出模块
        }
        else if (nSelect1 == 2)
        {
            PlayerChoice(); // 跳转到选项模块
        }
        else
        {
            printf("\n     逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。\n\n\n");
        }
    }
}
void PlayerChoice() // 选择玩家的身份
{
    int nSelect2; // 选择不同的模式，进入不同的角色
    printf("\n");
    printf("   欢迎进入游戏，请选择您的角色！  \n");
    printf("\n");
    printf("        输入   1 你是魔术师 \n");
    printf("        输入   2 你是观众  \n");
    printf("\n请输入相应的数字，进入不同的模块:  \n");
    printf("\n");
    scanf("%d", &nSelect2);
    getchar();
    if (nSelect2 == 1)
    {
        printf("     大魔术师欢迎您！  \n");
        printf("\n");
        Magician(); // 进入魔术师的角色；
    }
    else if (nSelect2 == 2)
    {
        printf("     亲爱的小伙伴。快提问吧，我已经准备好了！  \n");
        printf("\n");
        Viewer(); // 进入观众的角色；
    }
    else
    {
        printf("\n      逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。 \n");
    }
}
void ExitGame() // 退出模块函数
{
    char select; // 局部字符变量用于定义Y和N
    printf("\n 你确定退出游戏吗 ^-^ ？ 退出 请输入 Y 或 y , 继续点任意键 \n\n");
    scanf("%c", &select);
    getchar();
    if (select == 'Y' || select == 'y')
    {
        printf("\n     欢迎下次再来哦！！！    \n");
        exit(1);
    }
    else
    {
        return;
    }
}

/*Magician函数开始*/
void Magician()
{ // 玩家是魔术师
    printf("小龙：这次你出数字，我猜。\n");
    nNumber = rand() % 900 + 100; // 随机生成一个三位数

    nHundreds = nNumber / 100;
    nTens = (nNumber / 10) % 10;
    nOnes = nNumber % 10;
    nSum = 222 * (nHundreds + nTens + nOnes) - nNumber; // 计算五个数的和
    printf("电脑：我出的数字是：%d\n", nSum);

    printf("小龙：等等哈。\n");
    printf("小龙：哈哈，是不是");
    int nGuessNumber;
    scanf("%d", &nGuessNumber);
    if (nGuessNumber == nSum)
    {
        printf("电脑：魔术师真聪明！\n");
    }
    else
    {
        printf("电脑：我想的数字是%d，你好像猜错了呢！\n", nNumber);
    }
}

/*Viewer函数开始*/
void Viewer()
{ // 玩家是观众
    printf("小龙：我出的数字和是");
    scanf("%d", &nSum);

    printf("电脑：稍等2秒，我就能说出原来的数。\n");
    printf("小龙：等就等，猜吧！\n");
    if (nSum < 122 || nSum > 4995) // 判断输入的数字是否在范围内
    {
        printf("电脑：你出的数字不对吧！\n");
        return;
    }

    int nCon = nSum / 222; // 计算 nCon 的初始值

    while (true)
    {
        int remainder = nCon * 222 - nSum; // 计算余数

        if (remainder < 100)
        {
            nCon++;
            continue;
        }
        else if (remainder > 1000)
        {
            printf("电脑：我算不出来，你的数字和输对了吗。\n");
            return;
        }

        // 分解余数为 a, b, c
        int a = remainder / 100;
        int b = (remainder / 10) % 10;
        int c = remainder % 10;

        // 检查是否符合 (a + b + c) = nCon
        if (a + b + c == nCon)
        {
            printf("电脑：绝对是%d！\n", remainder);
            return;
        }

        nCon++;
    }
}
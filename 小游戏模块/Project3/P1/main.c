#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>    // 标准输入输出库
#include<conio.h>    // getch()函数需要的库
#include<stdlib.h>   // 标准库，包含rand()和srand()
#include<time.h>     // 时间函数库

static void clear_screen()
{
#ifdef _WIN32
    system("cls");  // Windows系统使用cls命令
#else
    system("clear"); // Linux/Mac系统使用clear命令
#endif
}

static void back()
{
    printf("点击任意键继续\n");
    int a = getch();  // 等待用户按键
    clear_screen();   // 清屏
}
//电脑计算玩家心里所想的函数
//return 0表示无解
//return Abc表示找到Abc
static int multiply(int* x)
{
    int i = *x / 222 + 1;  // 计算可能的最小数字和
    int Abc = 0;
    for (i; i < 28; i++)
    {
        Abc = i * 222 - *x; 
        if ((Abc / 100 + Abc % 100 / 10 + Abc % 10) == i)
        {
            return Abc;  // 找到解，返回三位数
        }
    }
        return 0;
}
//输入有效性检测并反馈
static void Input(int* x, int min, int max, char* say)
{
    while (1)
    {
        if (scanf("%d", x) != 1) 
        {
            printf("给我干哪里来了（@_@)?你输入的是数字吗？请重新输入\n");
            while (getchar() != '\n');
            continue;
        }
        else if (*x < min || *x > max)  // 检查范围
        {
            printf("%s\n", say);
            while (getchar() != '\n');
            continue;
        }
        else
            break;  // 输入有效，退出循环
    }
}
//游戏主菜单
static void menu1()
{
    printf(
        "┌─────────────────────┐ \n"
        "   欢迎游玩猜数字游戏     \n"
        "                        \n"
        "      1.开始新游戏       \n"
        "      2.游戏规则         \n"
        "      0.退出游戏         \n"
        "                        \n"
        "  t:熟练规则后再游戏！    \n"
        "└─────────────────────┘ \n"
    );
}
//游戏模式选择菜单
static void menu2()
{
    printf(
        "┌────────────────────────────┐  \n"
        "           游戏模式              \n"
        "         请选择您的身份          \n"
        "                               \n"
        "         1.我是魔术师           \n"
        "         2.我是观众             \n"
        "         0.退回至主菜单         \n"
        "                               \n"
        "                               \n"
        "└────────────────────────────┘ \n"
    );
}
//显示游戏规则
static void menu4()
{
    printf(
        "┌────────────────────────────────────────────┐\n"
        "        用户可作为:观众/魔术师 两种模式        \n"
        "                 观众模式：                    \n"
        " 魔术师(电脑)要求每一位观众心中想一个三位数abc!\n"
        "       a、b、c分别是百位,十位和个位数字        \n"
        " 观众心中记下acb,bac,bca,cab,cba这5个数的和值 \n"
        " 观众说出和值,魔术师就能猜到观众心里想的数abc\n"
        "                 魔术师模式：                  \n"
        "          观众(电脑)随机生成三位数abc!         \n"
        "        a、b、c分别是百位,十位和个位数字          \n"
        " 观众(电脑)输出acb,bac,bca,cab,cba这5个数的和值   \n"
        "         魔术师需要猜到观众心里想的数abc          \n"
        "└────────────────────────────────────────────┘ \n");
    back();
}
//电脑随机生成三位数并初始化在数组中
static void ABCnum(int* x)
{
    x[0] = rand() % 9 + 1;  // 百位1-9
    x[1] = rand() % 10;     // 十位0-9
    x[2] = rand() % 10;     // 个位0-9
    x[3] = x[0] + x[1] + x[2];  // 数字各位之和
    x[4] = 100 * x[0] + 10 * x[1] + x[2];  // 完整的三位数
}
//根据三位数计算其他五种组合数和值的函数
static void sum(int* x)
{
    int s[3] = { 0 };
    s[0] = *x / 100;      // 百位数
    s[1] = *x % 100 / 10; // 十位数
    s[2] = *x % 10;       // 个位数
    // 计算五个排列数的和：(a+b+c)*222 - abc
    int SUM = (s[0] + s[1] + s[2]) * 222 - *x;
    printf("求和结果为(%d%d%d+%d%d%d+%d%d%d+%d%d%d+%d%d%d=)'%d'\n你可不要把我给供出去了\n",
        s[2], s[0], s[1], s[1], s[2], s[0], s[1], s[0], s[2], s[0], s[2], s[1], s[2], s[1], s[0], SUM);
}
//观众模式函数
static void spectatemode()
{
    printf("援助计算机:五个数求和也太难算了吧,需要我帮你吗?(y/n)\n");
    char cinput;
    // 获取用户选择(y/n)
    while (1)
    {
        scanf(" %c", &cinput);
        if (cinput != 'y' && cinput != 'n')
        {
            printf("你瞅瞅你输入的对吗?请重新输入\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    // 用户选择帮助计算
    if (cinput == 'y')
    {
        printf("偷偷把你想的数（abc）告诉我吧,放心,我不会泄密的:^)\n");
        int num = 0;
        char say[] = "你在拿我寻开心吗？还是不知道什么是三位数(—_—)！";
        Input(&num, 100, 999, say);  // 获取三位数
        sum(&num);  // 计算并显示和值
        back();
    }
    // 用户自行计算和值
    int num = 0;
    int output = 0;
    printf("按照规则,求和结果是多少呢？");
    // 循环直到输入有效和值
    while (1)
    {
        char say[] = "我不用发动魔法就知道你在逗我，重新输入吧";
        Input(&num, 122, 4995, say);  // 获取和值
        output = multiply(&num);      // 计算原始三位数

        if (output == 0)
        {
            printf("不会吧不会吧，有人连加法都能算错，还是说，你随便输入一个数给我搞图灵测试呢 (~_~\")\n");
        }
        else
            break;
    }

    printf("你心里想的那个数是%d,对不对?都说了是魔法吧(￣ω￣),再来一局吧\n", output);
    back();
}
//魔术师模式函数
static void magicianmode()
{
    int num[5] = { 0 };  // 存储三位数相关信息
    ABCnum(num);         // 生成随机三位数

    int input3 = 0;
    printf("观众(电脑)：我已经想好了,求和结果是:'%d'\n", (num[3] * 222 - num[4]));
    printf("观众(电脑)：大魔术家,请开始你的表演（0_o）,猜猜我想的是什么数吧（^_^）\n");

    char say[] = "喂喂，你该不会是不知道什么是三位数吧？重新输入吧";
    Input(&input3, 100, 999, say);  // 获取玩家猜测

    printf("你的答案是'%d',正确答案是'%d'\n", input3, num[4]);
    // 判断猜测是否正确
    if (input3 == num[4])
    {
        int i = rand() % 4;
        if (i == 0)
        {
            printf("你怎么猜出来的(>_<),是不是偷看我代码了(←_←),我不服(｀へ′)再来一局 \n ");
        }
        else
        {
            printf("你很厉害嘛,要不要和我再玩一局,下一局你肯定猜不出来(｀へ′)\n");
        }
    }
    else
    {
        int i = rand() % 2;
        if (i == 0)
        {
            printf("菜,就多练,我的大魔术师连这都猜不中,你还是重开一局吧╮(╯▽╰)╭\n");
        }
        else
        {
            printf("恭喜你！！猜错啦(｀V') ,回去再练练吧！\n");
        }
    }
    back();
}
//进入新游戏时候的选择菜单
static void newgame()
{
    int input1 = 0;
    do
    {
        menu2();  // 显示模式选择菜单
        char say[] = "喂喂（*——*）！有这个选项吗？";
        Input(&input1, 0, 2, say);  // 获取模式选择

        switch (input1)
        {
        case 0:
            clear_screen();
            return;
        case 1:
            clear_screen();
            magicianmode();  // 进入魔术师模式
            break;
        case 2:
            clear_screen();
            spectatemode();  // 进入观众模式
            break;
        }
    } while (input1 != 0);
}
//主函数
int main()
{
    int input = 0;  // 用于存储输入选项
    srand(time(NULL));  // 初始化随机数种子
    do
    {
        menu1();  // 显示主菜单
        char say[] = "喂喂（*——*）！有这个选项吗？";
        Input(&input, 0, 2, say);  // 获取菜单选择

        switch (input)
        {
        case 0:
            return 0;  // 退出程序
        case 1:
            clear_screen();
            newgame();  // 开始新游戏
            break;
        case 2:
            clear_screen();
            menu4();  // 显示游戏规则
            break;
        }
    } while (input != 0);
    return 0;
}
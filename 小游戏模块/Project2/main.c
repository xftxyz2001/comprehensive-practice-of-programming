#include <stdio.h>  //包含标准输入输出库 ；
#include <stdlib.h> //包含标准库函数 ；
#include <time.h>   //包含日期和时间的头文件，用于需要时间方面的函数 ；
// 常量定义
#define MAXSCORE 2000 // 设定初始积分为2000
#define DICENUM 3     // 设定骰子数目为3

// 函数声明

// 输出游戏规则
void PrintGameRule();

// 获得随机掷骰子结果
void ThrowDice(int anDice[]);

// 收集玩家的输入
int GetInput(int nUScore, int nCScore, int *nChoice, int *nBetScore);

// 输出骰子状态
void OutputDice(int azDice[]);

// 根据玩家的选择计算输赢积分倍数
int JudgeChoice(int anDice[], int nChoice);

// 输出玩家选择后的输赢状态
void OutputStatus(int anDice[], int nChoice);

// 计算电脑和玩家目前的积分
int ComputeScore(int nTimes, int nBetScore, int *npUScore, int *pnCScore);

/*main函数开始*/
int main()
{
    int nComputerScore; // 电脑目前积分
    int nUserScore;     // 玩家目前积分
    // 给玩家和电脑赋予基本积分
    nComputerScore = nUserScore = MAXSCORE;
    int bContinue = 1;   // 设置标志量标示游戏是否结束
    int anDice[DICENUM]; // 存储每个骰子的数值
    int nChoice;         // 存放玩家的猜测
    int nBetScore;       // 存放玩家下注的积分数

    // 随机种子生成
    srand((unsigned)time(NULL));
    // 变成蓝底白字
    system("color 1f");
    // 输出游戏规则
    PrintGameRule();

    do // 根据玩家选择反复进行猜测
    {  // 收集玩家的输入,如果无效则重新输入
        bContinue = GetInput(nUserScore, nComputerScore, &nChoice, &nBetScore);
        if (bContinue == 0) // 玩家选择退出
            break;
        if (bContinue == 1) // 选择无效
            continue;

        // 让电脑扔骰子
        ThrowDice(anDice);
        // 判断玩家是否猜对了,返回输赢的倍数
        int nTimes = JudgeChoice(anDice, nChoice);
        // 给玩家输出目前的积分状态
        OutputStatus(anDice, nChoice);
        // 计算当前玩家和电脑的积分
        bContinue = ComputeScore(nTimes, nBetScore,
                                 &nUserScore, &nComputerScore);
    } while (bContinue != 0 && nChoice != 0);
    // 告别语
    printf("\n感谢您使用我们的程序！欢迎下次再玩儿！\n");
    return 0;
}
/*main函数结束*/

/*Print Game Rule函数开始*/
// 输出游戏的规则
void PrintGameRule()
{
    printf("\n\t\t****---------掷骰子游戏----------****\n\n:\n");
    printf("\t\t电脑每次随机模拟掷骰子（骰子数%d颗,每个骰子1-6点）!\n", DICENUM);
    printf("\t\t由您下注积分值，然后猜测骰子的和是 大、小 还是豹子! \n");
    printf("\t\t豹子就是几个骰子的值都一样！例如 3 3 3 !\n\n");
    printf("\t\t如果猜对了大、小，电脑就赔您下注的分数!\n");
    printf("\t\t当然，如果猜错了，您也得赔电脑下注的分数!\n\n");
    printf("\t\t如果您猜对了是豹子!\n");
    printf("\t\t厉害了，word哥，电脑就赔您下注的分数的5倍!\n");
    printf("\t\t当然，您说是豹子，结果不是，您也得赔5倍分数!\n\n");
    printf("\t\t请记住：您和电脑的最初积分都是%d！\n\n", MAXSCORE);
    printf("\t\t怎么样，跃跃欲试了吗？祝您好运！\n\n");
    printf("\t\t****---------------------------****\n\n");
}
/*Print Game Rule函数结束*/

/*ThrowDice函数开始*/
// 获得随机掷骰子结果
void ThrowDice(int anDice[])
{
    int i;
    for (i = 0; i < DICENUM; i++)
    {
        anDice[i] = rand() % 6 + 1;
    }
}
/*ThrowDice函数结束*/

/*GetInput函数开始*/
// 收集玩家的输入
int GetInput(int nUScore, int nCScore, int *nChoice, int *nBetScore)
{
    printf("\n\t\t当前电脑积分为%d，当前玩家积分为%d\n", nCScore, nUScore);
    printf("\t\t请输入您下注的积分数，输入0退出游戏：");
    // 获取玩家下注的积分数
    scanf("%d", nBetScore);
    if (*nBetScore == 0)
    {
        return 0;
    }
    // 下注的积分数小于等于0
    if (*nBetScore < 0)
    {
        printf("\t\t输入错误，请重新输入！（1-%d）\n", nUScore);
        return 1;
    }
    // 下注的积分数大于玩家积分数
    if (*nBetScore > nUScore)
    {
        printf("\t\t您的积分不足，请重新输入！（1-%d）\n", nUScore);
        return 1;
    }
    printf("\t\t请输入您猜测的骰子和值（1.大、2.小、3.豹子）：");
    scanf("%d", nChoice);
    if (*nChoice < 1 || *nChoice > 3)
    {
        printf("\t\t输入错误，请重新输入！（1-3）\n");
        return 1;
    }
    return 2;
}
/*GetInput函数结束*/

/*OutputDice函数开始*/
// 输出骰子状态
void OutputDice(int azDice[])
{
    printf("\t\t您掷出的骰子是：");
    for (int i = 0; i < DICENUM; i++)
    {
        printf("%d ", azDice[i]);
    }
    printf("\n");
}
/*OutputDice函数结束*/

int _JudgeChoice(int anDice[], int nChoice)
{
    int i, nSum = 0, count = 0;
    for (i = 0; i < DICENUM; i++)
    {
        nSum += anDice[i];
        if (anDice[i] == anDice[0])
        {
            count++;
        }
    }

    int nTimes = 0;
    if (nChoice == 1) // 大
    {
        if (nSum > 3.5 * DICENUM)
        {
            nTimes = 1;
        }
        else
        {
            nTimes = -1;
        }
    }
    else if (nChoice == 2) // 小
    {
        if (nSum < 3.5 * DICENUM)
        {
            nTimes = 1;
        }
        else
        {
            nTimes = -1;
        }
    }
    else if (nChoice == 3) // 豹子
    {
        if (count == DICENUM)
        {
            nTimes = 5;
        }
        else
        {
            nTimes = -5;
        }
    }
    return nTimes;
}

/*JudgeChoice函数开始*/
// 根据玩家的选择计算输赢积分倍数
int JudgeChoice(int anDice[], int nChoice)
{
    return _JudgeChoice(anDice, nChoice);
}
/*JudgeChoice函数结束*/

/*OutputStatus函数开始*/
// 输出玩家选择后的输赢状态
void OutputStatus(int anDice[], int nChoice)
{
    OutputDice(anDice);
    int nTimes = _JudgeChoice(anDice, nChoice);
    if (nTimes > 0)
    {
        printf("\t\t恭喜您，猜对了！\n\t\t电脑就赔您%d倍的下注积分！\n", nTimes);
    }
    else if (nTimes < 0)
    {
        printf("\t\t很遗憾，您猜错了。\n\t\t您将失去%d倍的下注积分！\n", -nTimes);
    }
}
/*OutputStatus函数结束*/

/*ComputeScore函数开始*/
// 计算电脑和玩家目前的积分
int ComputeScore(int nTimes, int nBetScore, int *npUScore, int *pnCScore)
{
    int score = nBetScore * nTimes;
    *npUScore += score;
    *pnCScore -= score;
    // printf("\t\t您当前积分为%d，电脑当前积分为%d\n", *npUScore, *pnCScore);
    if (*npUScore <= 0)
    {
        printf("\n\t\t您失去了所有的积分，游戏失败！\n");
        return 0;
    }
    else if (*pnCScore <= 0)
    {
        printf("\n\t\t您赢得了所有的积分，游戏胜利！\n");
        return 0;
    }
    return 1;
}
/*ComputeScore函数结束*/

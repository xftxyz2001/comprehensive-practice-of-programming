/*
8-1 掷骰子游戏

比大小押注赌输赢游戏，电脑庄家和玩家PK
事先设定好玩家和庄家的积分（2000分）
程序模拟N个骰子投掷，让玩家猜：大小/豹子
玩家选择下注多少分值，程序根据结果确定玩家的输赢
猜大小的胜方获得1倍下注积分，猜豹子胜方获得5倍下注积分，败方扣除相同积分
积分随着输赢改变后，重复掷骰子， 直到积分小于 0，游戏结束 。
*/


#include<stdio.h>                                            //包含标准输入输出库 ； 
#include<stdlib.h>                                            //包含标准库函数 ； 
#include<time.h>                //包含日期和时间的头文件，用于需要时间方面的函数 ； 
//常量定义 
#define MAXSCORE 2000// 设定初始积分为2000 
#define DICENUM 3 //设定骰子数目为3 

//函数声明

//输出游戏规则
void  PrintGameRule()                                                                  
{
	printf("\n\t\t****---------掷骰子游戏----------****\n\n:\n");         
    printf("\t\t电脑每次随机模拟掷骰子（骰子数%d颗,每个骰子1-6点）!\n",DICENUM); 
	printf("\t\t由您下注积分值，然后猜测骰子的和是 大、小 还是豹子! \n");
	printf("\t\t豹子就是几个骰子的值都一样！例如 3 3 3 !\n\n");
    printf("\t\t如果猜对了大、小，电脑就赔您下注的分数!\n");
    printf("\t\t当然，如果猜错了，您也得赔电脑下注的分数!\n\n");
    printf("\t\t如果您猜对了是豹子!\n");
	printf("\t\t厉害了，word哥，电脑就赔您下注的分数的5倍!\n");
	printf("\t\t当然，您说是豹子，结果不是，您也得赔5倍分数!\n\n");
	printf("\t\t请记住：您和电脑的最初积分都是%d！\n\n",MAXSCORE);
	printf("\t\t怎么样，跃跃欲试了吗？祝您好运！\n\n");
	printf("\t\t****---------------------------****\n\n");	
}                                       
//获得随机掷骰子结果
void  ThrowDice(int anDice[])
{
	for(int i=0;i<3;i++)
	{
		anDice[i]=rand()%6+1;
	}
}

//收集玩家的输入
int GetInput(int nUScore,int nCScore,int *nChoice,int *nBetScore)
{
	printf("当前积分情况：玩家：%d,电脑：%d\n请输入您的选择：0：退出；1：买大；2：买小；3：豹子\n",nUScore,nCScore); 
	scanf("%d",nChoice);
	if(*nChoice>=1&&*nChoice<=3)
	{
		printf("请输入您的下注积分：\n");
		scanf("%d",nBetScore);
		if(*nBetScore<=0)//积分输入无效 
		{
			printf("积分输入不正确，请重新输入：\n");
			return 1; 
		}
		
		else if(*nBetScore>nUScore)//输入积分不足 
			{
				printf("您的积分不足，请重新输入：\n"); 
				return 1;
			}
	else 
	return 2;//输入是有效的
	} 
	else if(*nChoice==0)//退出
	return 0; 
	else //其他无效输入 
	return 1;
}
//输出骰子状态 
void OutputDice(int azDice[])
{
		printf("电脑扔的骰子点数是：");
		for(int i=0;i<3;i++)
		{
			printf("%d ",azDice[i]);
		} 
		printf("\n");
}

//根据玩家的选择计算输赢积分倍数 
int JudgeChoice(int anDice[],int nChoice)
{
	//是否为豹子 
	if((anDice[0]==anDice[1])&&(anDice[1]==anDice[2]))//如果是豹子 
	{
		if(nChoice==3) //用户买豹子 
		return 5;
		else//但是玩家没卖豹子而买了大小 
		return -1;//猜错了 
	}
	else if(nChoice==3)//不是豹子但是玩家买了豹子 
    {
        return -5;// 扣5倍
    }
    //如果数字是1或者2 
	if(nChoice==1||nChoice==2)
	{
		//三个骰子3 4 5 6 7 8 9 10 |11 12 13 14 15 16 17 18
		//买大就是（ 11 12 13 14 15 16 17 18
		//买小就是（ 3 4 5 6 7 8 9 10
		int sum=0; 
        //计算三个数之和 
		for(int i=0;i<3;i++) 
		{
			sum+=anDice[i];
		}
		//比较大小
		
		if(sum>=11)//结果是大
		{
		if(nChoice==1) //用户买大 
		return 1;
		else//买错了 
	    return -1;
	    }
	else //否则结果就是小了 
	{
		if(nChoice==2) //用户买小 
		return 1;
		else//买错了 
		return -1;
	}
}
return 0; 
}

//输出玩家选择后的输赢状态 
void OutputStatus(int anDice[],int nChoice)
{
	//先输出骰子状态 
	OutputDice(anDice);
	int sum=0;
	//算三个数的和 
	 for(int i=0;i<3;i++) 
		{
			sum+=anDice[i];
		}
	printf("电脑扔的骰子和是：%d\n结果为：\n",sum);
	//豹子 
	if((anDice[0]==anDice[1])&&(anDice[1]==anDice[2]))
	printf("豹子!\n");
	//结果是大 
	else if(sum>=11)
    printf("大!\n");
    //结果是小 
    else
	printf("小!\n");
	//输出玩家输入的赌注
	printf("您的猜测是：\n"); 
	if(nChoice==1) 
	printf("大!\n");
	else if(nChoice==2)
	printf("小!\n");
	else if(nChoice==3) 
	printf("豹子!\n");
}

//计算电脑和玩家目前的积分 
int ComputeScore(int nTimes,int nBetScore, int *npUScore,int *pnCScore)
{
	//改变的数值
	int change=nTimes*nBetScore;
	if(change>0)//修改的积分值为正 
    {
    	
        *npUScore+=change;
        *pnCScore-=change;
        printf("您获得了%d积分!\n",change);
    }
    else //玩家输了 
    {
        *npUScore+=change; 
        *pnCScore-=change; //减去负得等于加正的
        printf("您失去了%d积分!\n",-change);
    }
    printf("当前积分情况：玩家:%d,电脑:%d\n",*npUScore,*pnCScore);
    if(*npUScore<=0)
    {
        printf("您的积分已用完，游戏不可以进行\n");
        return 0;
    }
    else if(*pnCScore<=0)
    {
        printf("电脑积分已用完，您已获胜!\n");
        return 0;
    }
    else 
    return 1; //继续游戏
 } 

/*main函数开始*/  
int main()                                              
{
    int nComputerScore;//电脑目前积分 
	int nUserScore;//玩家目前积分
    //给玩家和电脑赋予基本积分 
    nComputerScore=nUserScore=MAXSCORE;
    int bContinue=1;//设置标志量标示游戏是否结束
	int anDice[DICENUM];//存储每个骰子的数值 
	int nChoice;//存放玩家的猜测
	int nBetScore;//存放玩家下注的积分数 
	
	//随机种子生成 
	srand((unsigned)time(NULL));
	//变成蓝底白字 
	system("color 1f");                                                           
	 //输出游戏规则 
    PrintGameRule();
	 
	do//根据玩家选择反复进行猜测                                                          
	{    //收集玩家的输入,如果无效则重新输入 
			bContinue=GetInput(nUserScore,nComputerScore,&nChoice,&nBetScore);
			if(bContinue==0)//玩家选择退出
			   break; 
			if(bContinue==1)//选择无效 
				continue; 
			
			//让电脑扔骰子 
		    ThrowDice(anDice);
			//判断玩家是否猜对了,返回输赢的倍数 
			int nTimes=JudgeChoice(anDice,nChoice);
			//给玩家输出目前的积分状态
			OutputStatus(anDice,nChoice);
	        //计算当前玩家和电脑的积分
			bContinue=ComputeScore(nTimes,nBetScore,
			             &nUserScore,&nComputerScore);		
	}while(bContinue!=0&&nChoice!=0);                                               	
	//告别语
	printf("\n感谢您使用我们的程序！欢迎下次再玩儿！\n"); 
   	return 0;                                                                                                               
}
/*main函数结束*/

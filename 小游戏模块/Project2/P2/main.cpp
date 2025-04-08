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
void  ThrowDice(int anDice[]){
	int i;
	for(i=0;i<3;i++){
		anDice[i] = rand() % 6 + 1;
	}
} 
 
//收集玩家的输入
int GetInput(int nUScore,int nCScore,int* nChoice,int* nBetScore){
        while (1) {
        	printf("请选择押注类型（1-大，2-小，3-豹子 0-退出）：");
            scanf("%d",nChoice);
            if(*nChoice==0){
            	return 0;
			}
            if (*nChoice != 0 && *nChoice != 1 && *nChoice != 2 && *nChoice != 3) {
                printf("选项无效，请输入0-3之间的数字。\n");
                continue;
            }
			else {
                break;
            }
        }
        while (1) {
            printf("请输入下注分数（当前可用积分：%d）：", nUScore);
            if (scanf("%d", nBetScore) != 1) {
                printf("输入无效，请重新输入。\n");
                while (getchar() != '\n');
                continue;
            }
            if (*nBetScore <= 0) {
                printf("下注分数必须大于0。\n");
            } else if (*nBetScore > nUScore) {
                printf("下注分数超过玩家当前积分。\n");
            } else {
                break;
            }
        }
}

//输出骰子状态 
void OutputDice(int azDice[]){
	int sum = azDice[0] + azDice[1] + azDice[2];
	printf("骰子结果：%d %d %d 总和：%d \n", azDice[0], azDice[1], azDice[2],sum);
}

//根据玩家的选择计算输赢积分倍数 
int JudgeChoice(int anDice[],int nChoice){
	OutputDice(anDice);
	int sum = anDice[0] + anDice[1] + anDice[2];
	int is_leopard = (anDice[0] == anDice[1] && anDice[1] == anDice[2]);
	if (nChoice == 3) {
            if (is_leopard) {
                return 5;
            } else {
                return -5;
            }
        } else {
            int is_big = sum >= 11;
            int is_small = sum <= 10;
            int win = 0;

            if ((nChoice == 1 && is_big) || (nChoice == 2 && is_small)) {
                win = 1;
            }

            if (win) {
                return 1;
            } else {
                return -1;
            }
        }
}

//输出玩家选择后的输赢状态 
void OutputStatus(int anDice[],int nChoice){
	int sum = anDice[0] + anDice[1] + anDice[2];
	int is_leopard = (anDice[0] == anDice[1] && anDice[1] == anDice[2]);
	if (nChoice == 3) {
            if (is_leopard) {
                printf("您赢了，");
            } else {
                printf("您输了，");
            }
        } else {
            int is_big = sum >= 11;
            int is_small = sum <= 10;
            int win = 0;

            if ((nChoice == 1 && is_big) || (nChoice == 2 && is_small)) {
                win = 1;
            }

            if (win) {
                printf("您赢了，");
            } else {
                printf("您输了，");
            }
        }
}

//计算电脑和玩家目前的积分 
int ComputeScore(int nTimes,int nBetScore, int* npUScore,int *pnCScore){
	nBetScore *= nTimes;
	*npUScore += nBetScore;
    *pnCScore -= nBetScore;
    if(nTimes < 0){
    	printf("您失去了 %d 分 \n",-nBetScore); 
	} else{
		printf("您赢得了 %d 分 \n",nBetScore); 
	}
	if(*npUScore<=0){
		printf("您的积分不足，游戏结束！");
		return 0;
	}if(*pnCScore<=0){
		printf("庄家的积分不足，游戏结束！");
		return 0;
	}
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
			//让电脑扔骰子 
		    ThrowDice(anDice);
			//判断玩家是否猜对了,返回输赢的倍数 
			int nTimes=JudgeChoice(anDice,nChoice);
			//给玩家输出目前的积分状态
			OutputStatus(anDice,nChoice);
	        //计算当前玩家和电脑的积分
			bContinue=ComputeScore(nTimes,nBetScore,&nUserScore,&nComputerScore);		
	}while(bContinue!=0&&nChoice!=0);                                               	
	//告别语
	printf("\n感谢您使用我们的程序！欢迎下次再玩儿！\n"); 
   	return 0;                                                                                                               
}
/*main函数结束*/




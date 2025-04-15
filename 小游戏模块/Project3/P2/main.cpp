#include <stdio.h>                                 //包含标准输入输出库
#include <stdlib.h>                                //包含标准库函数
#include <windows.h>                               //包含定义了关于创建窗口，消息循环等函数，如果要用API来做有界面的程序的话，必须要用到这个头文件； 
#include <time.h>                                  //包含日期和时间的头文件，用于需要时间方面的函数 ；
#include <math.h>                                  //包含了很多数学方法的函数库 
/*头文件声明结束*/

/*函数声明开始*/

void MainMenu();                                  //菜单页面模块 
void PlayerChoice();                              //选项模块 
void ExitGame();                                  //退出模块 
void Magician();                                  //魔术师功能模块 
void Viewer() ;                                   //观众模块 
//int  InputFiveNumber();                            //输入5个数的值 
/*函数声明结束*/

/*定义全局变量开始*/
int nHundreds;                                    //百位 
int nTens;                                        //十位 
int nOnes;                                        //个位 
int nSum;                                         //计算的 5个数的和值
int nNumber;                                      //三位数的值
/*定义全局变量结束*/


int main()
{ 
	MainMenu();                                   //调用主菜单函数 
	return 0;                                     
}

void MainMenu()                                   //系统主菜单
{
 	
	int nSelect1;                                   //局部变量表示选项 
	while(1)
	{
		printf("-------------------------------Main Menu-------------------------------\n");
		printf("\n");
		printf("\t     1   退出\n");
		printf("\t     2   进入游戏\n");
		printf("请输入相应的数字，进入不同的模块:  \n");
		printf("-----------------------------------------------------------------------\n");
		scanf("%d",&nSelect1);
		getchar();
		fflush(stdin);
		if(nSelect1==1)
		{
			ExitGame();                           //跳转到退出模块 
		}
		else if(nSelect1==2)
		{
		  	PlayerChoice();                        //跳转到选项模块 
		}
		else
		{
			printf("\n     逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。\n\n\n");
		}
	}   
}
void PlayerChoice()                         //选择玩家的身份
{
	int nSelect2;                           //选择不同的模式，进入不同的角色  
	printf("\n");
	printf("   欢迎进入游戏，请选择您的角色！  \n");
	printf("\n");    
	printf("        输入   1 你是魔术师 \n");
	printf("        输入   2 你是观众  \n");
	printf("\n请输入相应的数字，进入不同的模块:  \n");
	printf("\n");
	scanf("%d",&nSelect2);
	getchar();
	if(nSelect2==1)
	{
		printf("     大魔术师欢迎您！  \n");
		printf("\n");
		Magician();          //进入魔术师的角色； 
	}
	else if(nSelect2==2)
	{
		printf("     亲爱的小伙伴。快提问吧，我已经准备好了！  \n");
	    printf("\n");
		Viewer();            //进入观众的角色；
	}
	else
	{
		printf("\n      逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。 \n");
	}	
}
void ExitGame()	                                          //退出模块函数 
{ 
	   char select;              //局部字符变量用于定义Y和N                                        
	   printf("\n 你确定退出游戏吗 ^-^ ？ 退出 请输入 Y 或 y , 继续点任意键 \n\n");
	   scanf( "%c",&select );
	   getchar();
	   if(select=='Y'||select=='y')
	   {
		   printf("\n     欢迎下次再来哦！！！    \n");	   
		   exit(1);
	   }
	   else
	   {
		   return;
	   }
}


void Magician(){                      //玩家是魔术师
		int nGuessNumber;
		int nCon=0;
		nNumber=rand()%900+100;
		nHundreds=nNumber/100;
		nTens=(nNumber/10)%10;
		nOnes=nNumber%10;
		nCon+=nHundreds*100;
		nCon+=nTens*10;
		nCon+=nOnes;
		printf("三位数的总和是：%d \n",nCon);
		printf("你的猜测是：");
		scanf("%d",&nGuessNumber);
		if(nNumber==nGuessNumber){
			printf("猜对了！\n");
		}
		else{
			printf("猜错了！正确答案是：%d \n",nNumber); 
		}
}
/*Viewer函数开始*/
void  Viewer(){  					//玩家是观众 
	int nCon;
	while(1){
		printf("请告诉我数字的总和：");
		scanf("%d",&nSum);
		if(122<=nSum && nSum<=4995){
			break;
		}
		else{
			printf("你这个数字有问题！");
			continue;
		}
	}
	nCon=nSum/222;
	nNumber=222*nCon;
	nNumber-=nSum;
	while(nNumber<100){
		nCon++;
		nNumber=222*nCon-nSum;
	}
	while(1){
		if(nNumber>1000){
			printf("这样的题目无解！\n");
			break;
		}
		nHundreds=nNumber/100;
		nTens=(nNumber/10)%10;
		nOnes=nNumber%10;
		if((nHundreds+nTens+nOnes)==nCon){
			printf("答案是：%d \n",nNumber);
			break;
		}
		else{
			nCon++;
			nNumber=222*nCon-nSum;
			continue; 
		}
	}
}







/*头文件声明开始*/
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


int main() {
	srand(time(0));
	MainMenu();                                   //调用主菜单函数
	return 0;
}

void MainMenu() {                                 //系统主菜单

	int nSelect1;                                   //局部变量表示选项
	while (1) {
		printf("-------------------------------Main Menu-------------------------------\n");
		printf("\n");
		printf("\t     1   退出\n");
		printf("\t     2   进入游戏\n");
		printf("请输入相应的数字，进入不同的模块:  \n");
		printf("-----------------------------------------------------------------------\n");
		scanf("%d", &nSelect1);
		getchar();
		fflush(stdin);
		if (nSelect1 == 1) {
			ExitGame();                           //跳转到退出模块
		} else if (nSelect1 == 2) {
			PlayerChoice();                        //跳转到选项模块
		} else {
			printf("\n     逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。\n\n\n");
		}
	}
}

void PlayerChoice() {                       //选择玩家的身份
	int nSelect2;                           //选择不同的模式，进入不同的角色
	printf("\n");
	printf("   欢迎进入游戏，请选择您的角色！  \n");
	printf("\n");
	printf("        输入   1 你是魔术师 \n");
	printf("        输入   2 你是观众  \n");
	printf("\n请输入相应的数字，进入不同的模块:  \n");
	printf("\n");
	scanf("%d", &nSelect2);
	getchar();
	if (nSelect2 == 1) {
		printf("     大魔术师欢迎您！  \n");
		printf("\n");
		Magician();          //进入魔术师的角色；
	} else if (nSelect2 == 2) {
		printf("     亲爱的小伙伴。快提问吧，我已经准备好了！  \n");
		printf("\n");
		Viewer();            //进入观众的角色；
	} else {
		printf("\n      逗我玩儿呢？   就没有那个选项好不！   请重新输入进行再次选择。 \n");
	}
}

void ExitGame() {                                          //退出模块函数
	char select;              //局部字符变量用于定义Y和N
	printf("\n 你确定退出游戏吗 ^-^ ？ 退出 请输入 Y 或 y , 继续点任意键 \n\n");
	scanf( "%c", &select );
	getchar();
	if (select == 'Y' || select == 'y') {
		printf("\n     欢迎下次再来哦！！！    \n");
		exit(1);
	} else {
		return;
	}
}


void Magician() {
	// 电脑随机生成一个三位数
	int number = 100 + rand() % 900;
	int a = number / 100;
	int b = (number / 10) % 10;
	int c = number % 10;

	// 计算五个排列数的和
	int sum = (a * 100 + c * 10 + b) + (b * 100 + a * 10 + c) +
	          (b * 100 + c * 10 + a) + (c * 100 + a * 10 + b) +
	          (c * 100 + b * 10 + a);

	printf("\n电脑已经想好了一个三位数！\n");
	printf("五个排列数的和是: %d\n", sum);
	printf("你能猜出原始数字吗？\n");

	int guess, attempts = 0;
	do {
		printf("你的猜测（100-999）: ");
		scanf("%d", &guess);
		attempts++;

		if (guess < number) {
			printf("猜小了！再试试看。\n");
		} else if (guess > number) {
			printf("猜大了！再试试看。\n");
		}
	} while (guess != number && attempts < 5);

	if (guess == number) {
		printf("\n恭喜你！猜对了！原始数字就是 %d\n", number);
	} else {
		printf("\n很遗憾，正确答案是 %d\n", number);
	}
	MainMenu();
}

void Viewer() {
	int number;
	int sum = 0;
	int max_attempts = 100;  // 防止死循环的最大尝试次数

	printf("请输入五个排列数的和（例如：如果原始数是 123，则五个排列数的和是 123 + 132 + 213 + 231 + 312 + 321 = 1332）:\n");
	scanf("%d", &sum);

	// 魔术师猜数的精确算法
	int nCon = sum / 222;  // 初始商数
	int remainder;
	int guessed_number = -1;
	int attempts = 0;  // 记录尝试次数

	while (attempts < max_attempts) {
		remainder = nCon * 222 - sum;

		if (remainder < 100) {
			nCon++;  // 余数太小，增加商数
		} else if (remainder > 999) {
			nCon--;  // 余数太大，减少商数
		} else {
			// 分解余数为 a, b, c
			int ga = remainder / 100;
			int gb = (remainder / 10) % 10;
			int gc = remainder % 10;

			if (ga + gb + gc == nCon) {
				guessed_number = remainder;
				break;  // 找到解
			} else {
				nCon++;  // 继续尝试下一个商数
			}
		}
		attempts++;
	}

	if (guessed_number != -1) {
		printf("\n你心里想的数字是......%d！\n", guessed_number);
	} else {
		printf("\n输入的和不合法，无法还原出正确的三位数！\n");
		printf("请检查输入是否正确（例如：原始数 123 的和是 1332）。\n");
	}

	MainMenu();
}
#include <iostream>
#include "SubFunction.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	int number1,number2;
	printf("Please input two numbers:");
	scanf("%d%d",&number1,&number2);
	int sum=Add(number1,number2);
	printf("The summation of two numbers are: %d+%d=%d",number1,number2,sum);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "sqrt.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int num;
    printf("请输入一个整数: ");
    scanf("%d", &num);
    
    printf("平方值: %d\n", square(num));  // ?:ml-citation{ref="2,5" data="citationList"}
    printf("平方根: %.2f\n", integer_sqrt(num));  // ?:ml-citation{ref="2,3" data="citationList"}
    
    return 0;
}

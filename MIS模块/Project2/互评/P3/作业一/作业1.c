#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "sqrt.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int num;
    printf("������һ������: ");
    scanf("%d", &num);
    
    printf("ƽ��ֵ: %d\n", square(num));  // ?:ml-citation{ref="2,5" data="citationList"}
    printf("ƽ����: %.2f\n", integer_sqrt(num));  // ?:ml-citation{ref="2,3" data="citationList"}
    
    return 0;
}

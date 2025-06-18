#include <stdio.h>
#include <conio.h>
#define N 6 
//假设用户名和密码均为6位
 
 
//目前的做法——调用 getchar()获取字符 

//新的函数——调用 getche()获取字符 ，立即读取，不以回车结束 
//函数名:getche()
//功 能:输入后立即从控制台取字符，不以回车为结束(带回显)

//需包含头文件：<conio.h>
//函数名:getch()
//功 能:输入后立即从控制台取字符，不以回车为结束(无回显)


int main() 
{
	char szUserName[N+1]; 
	char szUserPass[N+1];
	int i;
    printf("\n请输入%d位用户名：\n",N);
    for (i=0;i<N;i++)
      szUserName[i]=getche();//用getchar()时，在键盘上按一个字符后，要按回车才能读取进去。
      
    szUserName[i]='\0'; 

    fflush(stdin);//fflush(stdin) 的功能是：清空输入缓冲区。包含在文件 stdio.h 中。
    printf("\n请输入%d位密码：\n",N);
    for (i=0;i<N;i++)
    {
		szUserPass[i]=getch();
		putchar('*') ;
	}
    szUserPass[i]='\0';    
    
    printf("\nUser Name: %s User Password: %s\n",szUserName,szUserPass) ;
    return 0;
}


 


#include <stdio.h>
#include <conio.h>
#define N 6 
//�����û����������Ϊ6λ
 
 
//Ŀǰ�������������� getchar()��ȡ�ַ� 

//�µĺ����������� getche()��ȡ�ַ� ��������ȡ�����Իس����� 
//������:getche()
//�� ��:����������ӿ���̨ȡ�ַ������Իس�Ϊ����(������)

//�����ͷ�ļ���<conio.h>
//������:getch()
//�� ��:����������ӿ���̨ȡ�ַ������Իس�Ϊ����(�޻���)


int main() 
{
	char szUserName[N+1]; 
	char szUserPass[N+1];
	int i;
    printf("\n������%dλ�û�����\n",N);
    for (i=0;i<N;i++)
      szUserName[i]=getche();//��getchar()ʱ���ڼ����ϰ�һ���ַ���Ҫ���س����ܶ�ȡ��ȥ��
      
    szUserName[i]='\0'; 

    fflush(stdin);//fflush(stdin) �Ĺ����ǣ�������뻺�������������ļ� stdio.h �С�
    printf("\n������%dλ���룺\n",N);
    for (i=0;i<N;i++)
    {
		szUserPass[i]=getch();
		putchar('*') ;
	}
    szUserPass[i]='\0';    
    
    printf("\nUser Name: %s User Password: %s\n",szUserName,szUserPass) ;
    return 0;
}


 


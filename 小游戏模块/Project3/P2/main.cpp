#include <stdio.h>                                 //������׼���������
#include <stdlib.h>                                //������׼�⺯��
#include <windows.h>                               //���������˹��ڴ������ڣ���Ϣѭ���Ⱥ��������Ҫ��API�����н���ĳ���Ļ�������Ҫ�õ����ͷ�ļ��� 
#include <time.h>                                  //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��
#include <math.h>                                  //�����˺ܶ���ѧ�����ĺ����� 
/*ͷ�ļ���������*/

/*����������ʼ*/

void MainMenu();                                  //�˵�ҳ��ģ�� 
void PlayerChoice();                              //ѡ��ģ�� 
void ExitGame();                                  //�˳�ģ�� 
void Magician();                                  //ħ��ʦ����ģ�� 
void Viewer() ;                                   //����ģ�� 
//int  InputFiveNumber();                            //����5������ֵ 
/*������������*/

/*����ȫ�ֱ�����ʼ*/
int nHundreds;                                    //��λ 
int nTens;                                        //ʮλ 
int nOnes;                                        //��λ 
int nSum;                                         //����� 5�����ĺ�ֵ
int nNumber;                                      //��λ����ֵ
/*����ȫ�ֱ�������*/


int main()
{ 
	MainMenu();                                   //�������˵����� 
	return 0;                                     
}

void MainMenu()                                   //ϵͳ���˵�
{
 	
	int nSelect1;                                   //�ֲ�������ʾѡ�� 
	while(1)
	{
		printf("-------------------------------Main Menu-------------------------------\n");
		printf("\n");
		printf("\t     1   �˳�\n");
		printf("\t     2   ������Ϸ\n");
		printf("��������Ӧ�����֣����벻ͬ��ģ��:  \n");
		printf("-----------------------------------------------------------------------\n");
		scanf("%d",&nSelect1);
		getchar();
		fflush(stdin);
		if(nSelect1==1)
		{
			ExitGame();                           //��ת���˳�ģ�� 
		}
		else if(nSelect1==2)
		{
		  	PlayerChoice();                        //��ת��ѡ��ģ�� 
		}
		else
		{
			printf("\n     ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ��\n\n\n");
		}
	}   
}
void PlayerChoice()                         //ѡ����ҵ����
{
	int nSelect2;                           //ѡ��ͬ��ģʽ�����벻ͬ�Ľ�ɫ  
	printf("\n");
	printf("   ��ӭ������Ϸ����ѡ�����Ľ�ɫ��  \n");
	printf("\n");    
	printf("        ����   1 ����ħ��ʦ \n");
	printf("        ����   2 ���ǹ���  \n");
	printf("\n��������Ӧ�����֣����벻ͬ��ģ��:  \n");
	printf("\n");
	scanf("%d",&nSelect2);
	getchar();
	if(nSelect2==1)
	{
		printf("     ��ħ��ʦ��ӭ����  \n");
		printf("\n");
		Magician();          //����ħ��ʦ�Ľ�ɫ�� 
	}
	else if(nSelect2==2)
	{
		printf("     �װ���С��顣�����ʰɣ����Ѿ�׼�����ˣ�  \n");
	    printf("\n");
		Viewer();            //������ڵĽ�ɫ��
	}
	else
	{
		printf("\n      ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ�� \n");
	}	
}
void ExitGame()	                                          //�˳�ģ�麯�� 
{ 
	   char select;              //�ֲ��ַ��������ڶ���Y��N                                        
	   printf("\n ��ȷ���˳���Ϸ�� ^-^ �� �˳� ������ Y �� y , ����������� \n\n");
	   scanf( "%c",&select );
	   getchar();
	   if(select=='Y'||select=='y')
	   {
		   printf("\n     ��ӭ�´�����Ŷ������    \n");	   
		   exit(1);
	   }
	   else
	   {
		   return;
	   }
}


void Magician(){                      //�����ħ��ʦ
		int nGuessNumber;
		int nCon=0;
		nNumber=rand()%900+100;
		nHundreds=nNumber/100;
		nTens=(nNumber/10)%10;
		nOnes=nNumber%10;
		nCon+=nHundreds*100;
		nCon+=nTens*10;
		nCon+=nOnes;
		printf("��λ�����ܺ��ǣ�%d \n",nCon);
		printf("��Ĳ²��ǣ�");
		scanf("%d",&nGuessNumber);
		if(nNumber==nGuessNumber){
			printf("�¶��ˣ�\n");
		}
		else{
			printf("�´��ˣ���ȷ���ǣ�%d \n",nNumber); 
		}
}
/*Viewer������ʼ*/
void  Viewer(){  					//����ǹ��� 
	int nCon;
	while(1){
		printf("����������ֵ��ܺͣ�");
		scanf("%d",&nSum);
		if(122<=nSum && nSum<=4995){
			break;
		}
		else{
			printf("��������������⣡");
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
			printf("��������Ŀ�޽⣡\n");
			break;
		}
		nHundreds=nNumber/100;
		nTens=(nNumber/10)%10;
		nOnes=nNumber%10;
		if((nHundreds+nTens+nOnes)==nCon){
			printf("���ǣ�%d \n",nNumber);
			break;
		}
		else{
			nCon++;
			nNumber=222*nCon-nSum;
			continue; 
		}
	}
}







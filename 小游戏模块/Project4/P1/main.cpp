#include <stdio.h>               //������׼��������� �� 
#include <stdlib.h>              //������׼�⺯�� �� 
#include <time.h>               //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��                              
#include <windows.h>           //���������˹��ڴ������ڣ���Ϣѭ���Ⱥ����� 
  
/*����һ���ṹ��*/ 
typedef struct Card  
{  
	const char *number;                  //�����ַ���ָ�����number �� 
	char color;                    //�����ַ��ͱ���color �� 
} Card;                                 //������һ��card�Ľṹ�� �� 
/*�ṹ�嶨�����*/

/*����������ʼ*/
//�������ַ�������Card�ṹ��ĺ��� 
void FillDeck( Card * wDeck, const char * wNumber[], const char wColor[]);   
//����ϴ�Ƶĺ��� 
void Shuffle( Card * wDeck );         
//�������Ƶĺ���                                 
void Deal(Card * wDeck );                                        
//����д���ļ��ĺ��� 
void Write_File(Card * wDeck);  
//���������ļ��ĺ���                                          
int  Read_File(); 
//������ӡ����                                         
void Print();                                                            
void park();
/*������������*/
  
/*main������ʼ*/
int main()  
{   srand(time(NULL));   //����ʱ������ 
    Print();             // ��ӡ��ҳ�� 
	Card deck[ 52 ];      // ����Card������deck[]�����ڴ洢52���ƣ� 
    const char *number[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };      // ָ������ĳ�ʼ������ʾ13���� 
    const char color[]  = { 3,4,5,6 };   //����ĳ�ʼ������ʾ��ͬ��ɫ�� 
    
    FillDeck( deck, number, color );  //���ַ�������Card�ṹ�� 
    Shuffle(deck);                                              //ϴ��   
    Deal(deck);                                                 //����    
	Write_File(deck);                                             //д���ļ� 
	Read_File();                                                  //�����ļ� 
    return 0;  
}
/*main��������*/ 

/*Print������ʼ*/ 
void Print()                                                            //��ӡ��ҳ�� 
{
  	printf("\t_________________ϵͳ���ڼ����У����Ե�_____________________\t\n\n");
	for(int i=0;i<20;i++)
	{
		printf(".....");
		Sleep(200);	                                            //��ʱ��ӡ �� 
	}                                                          
	system("CLS");	                                            //���� ��   
	system("color 5F");	                                        //��ɫ����������ʮ����������ָ�� �� 5 = ��ɫ������ɫ�� F = ����ɫ��ǰ��ɫ����                                  

	printf("    **********************************************************************\n");
	Sleep(100);
    printf("    * A%c      *   |   * A%c      *   |   * A%c      *   |   * A%c      *\n",3,4,5,6);        //����ASCII���,ʮ���Ƶ�3�����ַ���ʾһ�����ģ� 
    Sleep(200);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    Sleep(250);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    Sleep(100);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    printf("    *       A%c*   |   *       A%c*   |   *       A%c*   |   *       A%c*\n",3,4,5,6);   
    Sleep(100);
    printf("    **********************************************************************\n");
    Sleep(100);
    printf("    ********************************ģ�ⷢ��******************************\n");
    printf("\n");
    printf("\n");
    printf("\n");
} 
/*Print��������*/ 
void FillDeck( Card * wDeck, const char * wNumber[], const char wColor[] )       
{
	for(int i=0;i<52;i++)
	{
		wDeck[i].number=wNumber[i%13];
		wDeck[i].color=wColor[i/13];
	}
}
void Shuffle( Card * wDeck )                 
{
	Card temp;
	for(int i=0;i<=51;i++)
	{
		int j=rand()%52;
		temp=wDeck[i];
		wDeck[i]=wDeck[j];
		wDeck[j]=temp;
	}
}
void Deal( Card * wDeck )                   
{
	for(int i=0;i<=51;i++)
	{
		if(i==0) printf("��һ���ƣ�\n");
		printf("%s-%c ",wDeck[i].number,wDeck[i].color);
		if(i==12) printf("\n�ڶ����ƣ�\n");
		if(i==25) printf("\n�������ƣ�\n");
		if(i==38) printf("\n�������ƣ�\n");
	}
	printf("\n");
}  
void Write_File(Card * wDeck){                                 
    FILE *fp = NULL;                           //����һ���ļ�ָ�� 
    fp= fopen("data.dat","wb");                  //д��һ��dat�ļ����������ļ� 
    if(fp == NULL)                              //�ж��Ƿ���Դ� 
    {
        printf("error!");
        return;
    }
    fwrite(wDeck,sizeof(Card),52,fp);
    fclose(fp);  	                                           //�ر��ļ�
    printf("\n\n=================================�� �� �� �� !=================================\n\n\n");
}
int Read_File()                                               
{
    char reply;                         //����һ���ַ�����������ʾ�Ƿ������Ϸ; 
    int i,a;                             //����ֲ�����i(����ѭ��),a(ѡ��); 
    do{
        Card wDeck[52];
        Card*pointer;               //����һ�� Card�͵�ָ��pointer�� 
        pointer=wDeck;             //�� pointerָ�� wDeck�� 
        FILE*fp = NULL;                                      //�����ļ�ָ�룻 
        fp = fopen("data.dat","rb");      //���ļ���Ĭ�ϵ�ַ��ִ���ļ��� �� 
        if(fp == NULL)  
        {
            printf("error!");
            return 0;
        } 
        fread(wDeck,sizeof(Card),52,fp);  
		fclose(fp);                                      //�ر�ָ�룻
		printf("�������뿴�ڼ����ƣ�1--4����");
        scanf("%d", &a);
        if (a < 1 || a > 4)
        {
            printf("�������������1��4֮������֣�\n");
            continue;
        }
        printf("\n��%d�����ǣ�\n", a);
        for (int i = (a - 1) * 13; i < a * 13; i++)
        {
            printf("%s-%c ", wDeck[i].number, wDeck[i].color);
        }
        printf("\n");
        printf("\n�Ƿ�����鿴��(Y/N)");
        scanf(" %c",&reply);
    }while(reply=='Y'||reply=='y');                             //������y����ѭ�� 
    return 1;
} 
void  park()
{
	
	int i,a=0;
	printf("        ��������ϴ����!       \n");
	while(a<15)   //ѭ��15��
	{ 
	    //ÿ��forѭ������ÿ����ɫ������ʱ�� 
		for(i=0;i<9;i++);
			system("color a");     //A = ����ɫ
		for(i=0;i<9;i++);
		    system("color b");     //B = ��ǳ��ɫ
		for(i=0;i<9;i++);
		    system("color c");     //C = ����ɫ
		for(i=0;i<9;i++);
		    system("color d");     //D = ����ɫ
		for(i=0;i<9;i++);
	    	system("color e");     //E = ����ɫ
        for(i=0;i<9;i++);
		    system("color f");     //F = ����
		a++;
	}	
	printf("\n\n\n        ϴ�ƽ���!        \n\n");
}

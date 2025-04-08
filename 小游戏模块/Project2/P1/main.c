/*
8-1 ��������Ϸ

�ȴ�СѺע����Ӯ��Ϸ������ׯ�Һ����PK
�����趨����Һ�ׯ�ҵĻ��֣�2000�֣�
����ģ��N������Ͷ��������Ҳ£���С/����
���ѡ����ע���ٷ�ֵ��������ݽ��ȷ����ҵ���Ӯ
�´�С��ʤ�����1����ע���֣��±���ʤ�����5����ע���֣��ܷ��۳���ͬ����
����������Ӯ�ı���ظ������ӣ� ֱ������С�� 0����Ϸ���� ��
*/


#include<stdio.h>                                            //������׼��������� �� 
#include<stdlib.h>                                            //������׼�⺯�� �� 
#include<time.h>                //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� �� 
//�������� 
#define MAXSCORE 2000// �趨��ʼ����Ϊ2000 
#define DICENUM 3 //�趨������ĿΪ3 

//��������

//�����Ϸ����
void  PrintGameRule()                                                                  
{
	printf("\n\t\t****---------��������Ϸ----------****\n\n:\n");         
    printf("\t\t����ÿ�����ģ�������ӣ�������%d��,ÿ������1-6�㣩!\n",DICENUM); 
	printf("\t\t������ע����ֵ��Ȼ��²����ӵĺ��� ��С ���Ǳ���! \n");
	printf("\t\t���Ӿ��Ǽ������ӵ�ֵ��һ�������� 3 3 3 !\n\n");
    printf("\t\t����¶��˴�С�����Ծ�������ע�ķ���!\n");
    printf("\t\t��Ȼ������´��ˣ���Ҳ���������ע�ķ���!\n\n");
    printf("\t\t������¶����Ǳ���!\n");
	printf("\t\t�����ˣ�word�磬���Ծ�������ע�ķ�����5��!\n");
	printf("\t\t��Ȼ����˵�Ǳ��ӣ�������ǣ���Ҳ����5������!\n\n");
	printf("\t\t���ס�����͵��Ե�������ֶ���%d��\n\n",MAXSCORE);
	printf("\t\t��ô����ԾԾ��������ף�����ˣ�\n\n");
	printf("\t\t****---------------------------****\n\n");	
}                                       
//�����������ӽ��
void  ThrowDice(int anDice[])
{
	for(int i=0;i<3;i++)
	{
		anDice[i]=rand()%6+1;
	}
}

//�ռ���ҵ�����
int GetInput(int nUScore,int nCScore,int *nChoice,int *nBetScore)
{
	printf("��ǰ�����������ң�%d,���ԣ�%d\n����������ѡ��0���˳���1�����2����С��3������\n",nUScore,nCScore); 
	scanf("%d",nChoice);
	if(*nChoice>=1&&*nChoice<=3)
	{
		printf("������������ע���֣�\n");
		scanf("%d",nBetScore);
		if(*nBetScore<=0)//����������Ч 
		{
			printf("�������벻��ȷ�����������룺\n");
			return 1; 
		}
		
		else if(*nBetScore>nUScore)//������ֲ��� 
			{
				printf("���Ļ��ֲ��㣬���������룺\n"); 
				return 1;
			}
	else 
	return 2;//��������Ч��
	} 
	else if(*nChoice==0)//�˳�
	return 0; 
	else //������Ч���� 
	return 1;
}
//�������״̬ 
void OutputDice(int azDice[])
{
		printf("�����ӵ����ӵ����ǣ�");
		for(int i=0;i<3;i++)
		{
			printf("%d ",azDice[i]);
		} 
		printf("\n");
}

//������ҵ�ѡ�������Ӯ���ֱ��� 
int JudgeChoice(int anDice[],int nChoice)
{
	//�Ƿ�Ϊ���� 
	if((anDice[0]==anDice[1])&&(anDice[1]==anDice[2]))//����Ǳ��� 
	{
		if(nChoice==3) //�û����� 
		return 5;
		else//�������û�����Ӷ����˴�С 
		return -1;//�´��� 
	}
	else if(nChoice==3)//���Ǳ��ӵ���������˱��� 
    {
        return -5;// ��5��
    }
    //���������1����2 
	if(nChoice==1||nChoice==2)
	{
		//��������3 4 5 6 7 8 9 10 |11 12 13 14 15 16 17 18
		//�����ǣ� 11 12 13 14 15 16 17 18
		//��С���ǣ� 3 4 5 6 7 8 9 10
		int sum=0; 
        //����������֮�� 
		for(int i=0;i<3;i++) 
		{
			sum+=anDice[i];
		}
		//�Ƚϴ�С
		
		if(sum>=11)//����Ǵ�
		{
		if(nChoice==1) //�û���� 
		return 1;
		else//����� 
	    return -1;
	    }
	else //����������С�� 
	{
		if(nChoice==2) //�û���С 
		return 1;
		else//����� 
		return -1;
	}
}
return 0; 
}

//������ѡ������Ӯ״̬ 
void OutputStatus(int anDice[],int nChoice)
{
	//���������״̬ 
	OutputDice(anDice);
	int sum=0;
	//���������ĺ� 
	 for(int i=0;i<3;i++) 
		{
			sum+=anDice[i];
		}
	printf("�����ӵ����Ӻ��ǣ�%d\n���Ϊ��\n",sum);
	//���� 
	if((anDice[0]==anDice[1])&&(anDice[1]==anDice[2]))
	printf("����!\n");
	//����Ǵ� 
	else if(sum>=11)
    printf("��!\n");
    //�����С 
    else
	printf("С!\n");
	//����������Ķ�ע
	printf("���Ĳ²��ǣ�\n"); 
	if(nChoice==1) 
	printf("��!\n");
	else if(nChoice==2)
	printf("С!\n");
	else if(nChoice==3) 
	printf("����!\n");
}

//������Ժ����Ŀǰ�Ļ��� 
int ComputeScore(int nTimes,int nBetScore, int *npUScore,int *pnCScore)
{
	//�ı����ֵ
	int change=nTimes*nBetScore;
	if(change>0)//�޸ĵĻ���ֵΪ�� 
    {
    	
        *npUScore+=change;
        *pnCScore-=change;
        printf("�������%d����!\n",change);
    }
    else //������� 
    {
        *npUScore+=change; 
        *pnCScore-=change; //��ȥ���õ��ڼ�����
        printf("��ʧȥ��%d����!\n",-change);
    }
    printf("��ǰ������������:%d,����:%d\n",*npUScore,*pnCScore);
    if(*npUScore<=0)
    {
        printf("���Ļ��������꣬��Ϸ�����Խ���\n");
        return 0;
    }
    else if(*pnCScore<=0)
    {
        printf("���Ի��������꣬���ѻ�ʤ!\n");
        return 0;
    }
    else 
    return 1; //������Ϸ
 } 

/*main������ʼ*/  
int main()                                              
{
    int nComputerScore;//����Ŀǰ���� 
	int nUserScore;//���Ŀǰ����
    //����Һ͵��Ը���������� 
    nComputerScore=nUserScore=MAXSCORE;
    int bContinue=1;//���ñ�־����ʾ��Ϸ�Ƿ����
	int anDice[DICENUM];//�洢ÿ�����ӵ���ֵ 
	int nChoice;//�����ҵĲ²�
	int nBetScore;//��������ע�Ļ����� 
	
	//����������� 
	srand((unsigned)time(NULL));
	//������װ��� 
	system("color 1f");                                                           
	 //�����Ϸ���� 
    PrintGameRule();
	 
	do//�������ѡ�񷴸����в²�                                                          
	{    //�ռ���ҵ�����,�����Ч���������� 
			bContinue=GetInput(nUserScore,nComputerScore,&nChoice,&nBetScore);
			if(bContinue==0)//���ѡ���˳�
			   break; 
			if(bContinue==1)//ѡ����Ч 
				continue; 
			
			//�õ��������� 
		    ThrowDice(anDice);
			//�ж�����Ƿ�¶���,������Ӯ�ı��� 
			int nTimes=JudgeChoice(anDice,nChoice);
			//��������Ŀǰ�Ļ���״̬
			OutputStatus(anDice,nChoice);
	        //���㵱ǰ��Һ͵��ԵĻ���
			bContinue=ComputeScore(nTimes,nBetScore,
			             &nUserScore,&nComputerScore);		
	}while(bContinue!=0&&nChoice!=0);                                               	
	//�����
	printf("\n��л��ʹ�����ǵĳ��򣡻�ӭ�´��������\n"); 
   	return 0;                                                                                                               
}
/*main��������*/

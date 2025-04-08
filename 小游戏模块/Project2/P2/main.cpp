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
void  ThrowDice(int anDice[]){
	int i;
	for(i=0;i<3;i++){
		anDice[i] = rand() % 6 + 1;
	}
} 
 
//�ռ���ҵ�����
int GetInput(int nUScore,int nCScore,int* nChoice,int* nBetScore){
        while (1) {
        	printf("��ѡ��Ѻע���ͣ�1-��2-С��3-���� 0-�˳�����");
            scanf("%d",nChoice);
            if(*nChoice==0){
            	return 0;
			}
            if (*nChoice != 0 && *nChoice != 1 && *nChoice != 2 && *nChoice != 3) {
                printf("ѡ����Ч��������0-3֮������֡�\n");
                continue;
            }
			else {
                break;
            }
        }
        while (1) {
            printf("��������ע��������ǰ���û��֣�%d����", nUScore);
            if (scanf("%d", nBetScore) != 1) {
                printf("������Ч�����������롣\n");
                while (getchar() != '\n');
                continue;
            }
            if (*nBetScore <= 0) {
                printf("��ע�����������0��\n");
            } else if (*nBetScore > nUScore) {
                printf("��ע����������ҵ�ǰ���֡�\n");
            } else {
                break;
            }
        }
}

//�������״̬ 
void OutputDice(int azDice[]){
	int sum = azDice[0] + azDice[1] + azDice[2];
	printf("���ӽ����%d %d %d �ܺͣ�%d \n", azDice[0], azDice[1], azDice[2],sum);
}

//������ҵ�ѡ�������Ӯ���ֱ��� 
int JudgeChoice(int anDice[],int nChoice){
	OutputDice(anDice);
	int sum = anDice[0] + anDice[1] + anDice[2];
	int is_leopard = (anDice[0] == anDice[1] && anDice[1] == anDice[2]);
	if (nChoice == 3) {
            if (is_leopard) {
                return 5;
            } else {
                return -5;
            }
        } else {
            int is_big = sum >= 11;
            int is_small = sum <= 10;
            int win = 0;

            if ((nChoice == 1 && is_big) || (nChoice == 2 && is_small)) {
                win = 1;
            }

            if (win) {
                return 1;
            } else {
                return -1;
            }
        }
}

//������ѡ������Ӯ״̬ 
void OutputStatus(int anDice[],int nChoice){
	int sum = anDice[0] + anDice[1] + anDice[2];
	int is_leopard = (anDice[0] == anDice[1] && anDice[1] == anDice[2]);
	if (nChoice == 3) {
            if (is_leopard) {
                printf("��Ӯ�ˣ�");
            } else {
                printf("�����ˣ�");
            }
        } else {
            int is_big = sum >= 11;
            int is_small = sum <= 10;
            int win = 0;

            if ((nChoice == 1 && is_big) || (nChoice == 2 && is_small)) {
                win = 1;
            }

            if (win) {
                printf("��Ӯ�ˣ�");
            } else {
                printf("�����ˣ�");
            }
        }
}

//������Ժ����Ŀǰ�Ļ��� 
int ComputeScore(int nTimes,int nBetScore, int* npUScore,int *pnCScore){
	nBetScore *= nTimes;
	*npUScore += nBetScore;
    *pnCScore -= nBetScore;
    if(nTimes < 0){
    	printf("��ʧȥ�� %d �� \n",-nBetScore); 
	} else{
		printf("��Ӯ���� %d �� \n",nBetScore); 
	}
	if(*npUScore<=0){
		printf("���Ļ��ֲ��㣬��Ϸ������");
		return 0;
	}if(*pnCScore<=0){
		printf("ׯ�ҵĻ��ֲ��㣬��Ϸ������");
		return 0;
	}
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
			//�õ��������� 
		    ThrowDice(anDice);
			//�ж�����Ƿ�¶���,������Ӯ�ı��� 
			int nTimes=JudgeChoice(anDice,nChoice);
			//��������Ŀǰ�Ļ���״̬
			OutputStatus(anDice,nChoice);
	        //���㵱ǰ��Һ͵��ԵĻ���
			bContinue=ComputeScore(nTimes,nBetScore,&nUserScore,&nComputerScore);		
	}while(bContinue!=0&&nChoice!=0);                                               	
	//�����
	printf("\n��л��ʹ�����ǵĳ��򣡻�ӭ�´��������\n"); 
   	return 0;                                                                                                               
}
/*main��������*/




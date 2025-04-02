#include <stdio.h>  //������׼��������� ��
#include <stdlib.h> //������׼�⺯�� ��
#include <time.h>   //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��
// ��������
#define MAXSCORE 2000 // �趨��ʼ����Ϊ2000
#define DICENUM 3     // �趨������ĿΪ3

// ��������

// �����Ϸ����
void PrintGameRule();

// �����������ӽ��
void ThrowDice(int anDice[]);

// �ռ���ҵ�����
int GetInput(int nUScore, int nCScore, int *nChoice, int *nBetScore);

// �������״̬
void OutputDice(int azDice[]);

// ������ҵ�ѡ�������Ӯ���ֱ���
int JudgeChoice(int anDice[], int nChoice);

// ������ѡ������Ӯ״̬
void OutputStatus(int anDice[], int nChoice);

// ������Ժ����Ŀǰ�Ļ���
int ComputeScore(int nTimes, int nBetScore, int *npUScore, int *pnCScore);

/*main������ʼ*/
int main()
{
    int nComputerScore; // ����Ŀǰ����
    int nUserScore;     // ���Ŀǰ����
    // ����Һ͵��Ը����������
    nComputerScore = nUserScore = MAXSCORE;
    int bContinue = 1;   // ���ñ�־����ʾ��Ϸ�Ƿ����
    int anDice[DICENUM]; // �洢ÿ�����ӵ���ֵ
    int nChoice;         // �����ҵĲ²�
    int nBetScore;       // ��������ע�Ļ�����

    // �����������
    srand((unsigned)time(NULL));
    // ������װ���
    system("color 1f");
    // �����Ϸ����
    PrintGameRule();

    do // �������ѡ�񷴸����в²�
    {  // �ռ���ҵ�����,�����Ч����������
        bContinue = GetInput(nUserScore, nComputerScore, &nChoice, &nBetScore);
        if (bContinue == 0) // ���ѡ���˳�
            break;
        if (bContinue == 1) // ѡ����Ч
            continue;

        // �õ���������
        ThrowDice(anDice);
        // �ж�����Ƿ�¶���,������Ӯ�ı���
        int nTimes = JudgeChoice(anDice, nChoice);
        // ��������Ŀǰ�Ļ���״̬
        OutputStatus(anDice, nChoice);
        // ���㵱ǰ��Һ͵��ԵĻ���
        bContinue = ComputeScore(nTimes, nBetScore,
                                 &nUserScore, &nComputerScore);
    } while (bContinue != 0 && nChoice != 0);
    // �����
    printf("\n��л��ʹ�����ǵĳ��򣡻�ӭ�´��������\n");
    return 0;
}
/*main��������*/

/*Print Game Rule������ʼ*/
// �����Ϸ�Ĺ���
void PrintGameRule()
{
    printf("\n\t\t****---------��������Ϸ----------****\n\n:\n");
    printf("\t\t����ÿ�����ģ�������ӣ�������%d��,ÿ������1-6�㣩!\n", DICENUM);
    printf("\t\t������ע����ֵ��Ȼ��²����ӵĺ��� ��С ���Ǳ���! \n");
    printf("\t\t���Ӿ��Ǽ������ӵ�ֵ��һ�������� 3 3 3 !\n\n");
    printf("\t\t����¶��˴�С�����Ծ�������ע�ķ���!\n");
    printf("\t\t��Ȼ������´��ˣ���Ҳ���������ע�ķ���!\n\n");
    printf("\t\t������¶����Ǳ���!\n");
    printf("\t\t�����ˣ�word�磬���Ծ�������ע�ķ�����5��!\n");
    printf("\t\t��Ȼ����˵�Ǳ��ӣ�������ǣ���Ҳ����5������!\n\n");
    printf("\t\t���ס�����͵��Ե�������ֶ���%d��\n\n", MAXSCORE);
    printf("\t\t��ô����ԾԾ��������ף�����ˣ�\n\n");
    printf("\t\t****---------------------------****\n\n");
}
/*Print Game Rule��������*/

/*ThrowDice������ʼ*/
// �����������ӽ��
void ThrowDice(int anDice[])
{
    int i;
    for (i = 0; i < DICENUM; i++)
    {
        anDice[i] = rand() % 6 + 1;
    }
}
/*ThrowDice��������*/

/*GetInput������ʼ*/
// �ռ���ҵ�����
int GetInput(int nUScore, int nCScore, int *nChoice, int *nBetScore)
{
    printf("\n\t\t��ǰ���Ի���Ϊ%d����ǰ��һ���Ϊ%d\n", nCScore, nUScore);
    printf("\t\t����������ע�Ļ�����������0�˳���Ϸ��");
    // ��ȡ�����ע�Ļ�����
    scanf("%d", nBetScore);
    if (*nBetScore == 0)
    {
        return 0;
    }
    // ��ע�Ļ�����С�ڵ���0
    if (*nBetScore < 0)
    {
        printf("\t\t����������������룡��1-%d��\n", nUScore);
        return 1;
    }
    // ��ע�Ļ�����������һ�����
    if (*nBetScore > nUScore)
    {
        printf("\t\t���Ļ��ֲ��㣬���������룡��1-%d��\n", nUScore);
        return 1;
    }
    printf("\t\t���������²�����Ӻ�ֵ��1.��2.С��3.���ӣ���");
    scanf("%d", nChoice);
    if (*nChoice < 1 || *nChoice > 3)
    {
        printf("\t\t����������������룡��1-3��\n");
        return 1;
    }
    return 2;
}
/*GetInput��������*/

/*OutputDice������ʼ*/
// �������״̬
void OutputDice(int azDice[])
{
    printf("\t\t�������������ǣ�");
    for (int i = 0; i < DICENUM; i++)
    {
        printf("%d ", azDice[i]);
    }
    printf("\n");
}
/*OutputDice��������*/

int _JudgeChoice(int anDice[], int nChoice)
{
    int i, nSum = 0, count = 0;
    for (i = 0; i < DICENUM; i++)
    {
        nSum += anDice[i];
        if (anDice[i] == anDice[0])
        {
            count++;
        }
    }

    int nTimes = 0;
    if (nChoice == 1) // ��
    {
        if (nSum > 3.5 * DICENUM)
        {
            nTimes = 1;
        }
        else
        {
            nTimes = -1;
        }
    }
    else if (nChoice == 2) // С
    {
        if (nSum < 3.5 * DICENUM)
        {
            nTimes = 1;
        }
        else
        {
            nTimes = -1;
        }
    }
    else if (nChoice == 3) // ����
    {
        if (count == DICENUM)
        {
            nTimes = 5;
        }
        else
        {
            nTimes = -5;
        }
    }
    return nTimes;
}

/*JudgeChoice������ʼ*/
// ������ҵ�ѡ�������Ӯ���ֱ���
int JudgeChoice(int anDice[], int nChoice)
{
    return _JudgeChoice(anDice, nChoice);
}
/*JudgeChoice��������*/

/*OutputStatus������ʼ*/
// ������ѡ������Ӯ״̬
void OutputStatus(int anDice[], int nChoice)
{
    OutputDice(anDice);
    int nTimes = _JudgeChoice(anDice, nChoice);
    if (nTimes > 0)
    {
        printf("\t\t��ϲ�����¶��ˣ�\n\t\t���Ծ�����%d������ע���֣�\n", nTimes);
    }
    else if (nTimes < 0)
    {
        printf("\t\t���ź������´��ˡ�\n\t\t����ʧȥ%d������ע���֣�\n", -nTimes);
    }
}
/*OutputStatus��������*/

/*ComputeScore������ʼ*/
// ������Ժ����Ŀǰ�Ļ���
int ComputeScore(int nTimes, int nBetScore, int *npUScore, int *pnCScore)
{
    int score = nBetScore * nTimes;
    *npUScore += score;
    *pnCScore -= score;
    // printf("\t\t����ǰ����Ϊ%d�����Ե�ǰ����Ϊ%d\n", *npUScore, *pnCScore);
    if (*npUScore <= 0)
    {
        printf("\n\t\t��ʧȥ�����еĻ��֣���Ϸʧ�ܣ�\n");
        return 0;
    }
    else if (*pnCScore <= 0)
    {
        printf("\n\t\t��Ӯ�������еĻ��֣���Ϸʤ����\n");
        return 0;
    }
    return 1;
}
/*ComputeScore��������*/

/*ͷ�ļ�������ʼ*/
#include <stdio.h>   //������׼���������
#include <stdlib.h>  //������׼�⺯��
#include <windows.h> //���������˹��ڴ������ڣ���Ϣѭ���Ⱥ��������Ҫ��API�����н���ĳ���Ļ�������Ҫ�õ����ͷ�ļ���
#include <time.h>    //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��
#include <math.h>    //�����˺ܶ���ѧ�����ĺ�����
/*ͷ�ļ���������*/

/*����������ʼ*/

void MainMenu();     // �˵�ҳ��ģ��
void PlayerChoice(); // ѡ��ģ��
void ExitGame();     // �˳�ģ��
void Magician();     // ħ��ʦ����ģ��
void Viewer();       // ����ģ��
// int  InputFiveNumber();                            //����5������ֵ
/*������������*/

/*����ȫ�ֱ�����ʼ*/
int nHundreds; // ��λ
int nTens;     // ʮλ
int nOnes;     // ��λ
int nSum;      // ����� 5�����ĺ�ֵ
int nNumber;   // ��λ����ֵ
/*����ȫ�ֱ�������*/

int main()
{
    MainMenu(); // �������˵�����
    return 0;
}

void MainMenu() // ϵͳ���˵�
{

    int nSelect1; // �ֲ�������ʾѡ��
    while (1)
    {
        printf("-------------------------------Main Menu-------------------------------\n");
        printf("\n");
        printf("\t     1   �˳�\n");
        printf("\t     2   ������Ϸ\n");
        printf("��������Ӧ�����֣����벻ͬ��ģ��:  \n");
        printf("-----------------------------------------------------------------------\n");
        scanf("%d", &nSelect1);
        getchar();
        fflush(stdin);
        if (nSelect1 == 1)
        {
            ExitGame(); // ��ת���˳�ģ��
        }
        else if (nSelect1 == 2)
        {
            PlayerChoice(); // ��ת��ѡ��ģ��
        }
        else
        {
            printf("\n     ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ��\n\n\n");
        }
    }
}
void PlayerChoice() // ѡ����ҵ����
{
    int nSelect2; // ѡ��ͬ��ģʽ�����벻ͬ�Ľ�ɫ
    printf("\n");
    printf("   ��ӭ������Ϸ����ѡ�����Ľ�ɫ��  \n");
    printf("\n");
    printf("        ����   1 ����ħ��ʦ \n");
    printf("        ����   2 ���ǹ���  \n");
    printf("\n��������Ӧ�����֣����벻ͬ��ģ��:  \n");
    printf("\n");
    scanf("%d", &nSelect2);
    getchar();
    if (nSelect2 == 1)
    {
        printf("     ��ħ��ʦ��ӭ����  \n");
        printf("\n");
        Magician(); // ����ħ��ʦ�Ľ�ɫ��
    }
    else if (nSelect2 == 2)
    {
        printf("     �װ���С��顣�����ʰɣ����Ѿ�׼�����ˣ�  \n");
        printf("\n");
        Viewer(); // ������ڵĽ�ɫ��
    }
    else
    {
        printf("\n      ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ�� \n");
    }
}
void ExitGame() // �˳�ģ�麯��
{
    char select; // �ֲ��ַ��������ڶ���Y��N
    printf("\n ��ȷ���˳���Ϸ�� ^-^ �� �˳� ������ Y �� y , ����������� \n\n");
    scanf("%c", &select);
    getchar();
    if (select == 'Y' || select == 'y')
    {
        printf("\n     ��ӭ�´�����Ŷ������    \n");
        exit(1);
    }
    else
    {
        return;
    }
}

/*Magician������ʼ*/
void Magician()
{ // �����ħ��ʦ
    printf("С�������������֣��Ҳ¡�\n");
    nNumber = rand() % 900 + 100; // �������һ����λ��

    nHundreds = nNumber / 100;
    nTens = (nNumber / 10) % 10;
    nOnes = nNumber % 10;
    nSum = 222 * (nHundreds + nTens + nOnes) - nNumber; // ����������ĺ�
    printf("���ԣ��ҳ��������ǣ�%d\n", nSum);

    printf("С�����ȵȹ���\n");
    printf("С�����������ǲ���");
    int nGuessNumber;
    scanf("%d", &nGuessNumber);
    if (nGuessNumber == nSum)
    {
        printf("���ԣ�ħ��ʦ�������\n");
    }
    else
    {
        printf("���ԣ������������%d�������´����أ�\n", nNumber);
    }
}

/*Viewer������ʼ*/
void Viewer()
{ // ����ǹ���
    printf("С�����ҳ������ֺ���");
    scanf("%d", &nSum);

    printf("���ԣ��Ե�2�룬�Ҿ���˵��ԭ��������\n");
    printf("С�����Ⱦ͵ȣ��°ɣ�\n");
    if (nSum < 122 || nSum > 4995) // �ж�����������Ƿ��ڷ�Χ��
    {
        printf("���ԣ���������ֲ��԰ɣ�\n");
        return;
    }

    int nCon = nSum / 222; // ���� nCon �ĳ�ʼֵ

    while (true)
    {
        int remainder = nCon * 222 - nSum; // ��������

        if (remainder < 100)
        {
            nCon++;
            continue;
        }
        else if (remainder > 1000)
        {
            printf("���ԣ����㲻������������ֺ��������\n");
            return;
        }

        // �ֽ�����Ϊ a, b, c
        int a = remainder / 100;
        int b = (remainder / 10) % 10;
        int c = remainder % 10;

        // ����Ƿ���� (a + b + c) = nCon
        if (a + b + c == nCon)
        {
            printf("���ԣ�������%d��\n", remainder);
            return;
        }

        nCon++;
    }
}
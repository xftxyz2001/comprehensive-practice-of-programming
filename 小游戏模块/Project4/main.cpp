/*ͷ�ļ�������ʼ*/
#include <stdio.h>   //������׼��������� ��
#include <stdlib.h>  //������׼�⺯�� ��
#include <time.h>    //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��
#include <windows.h> //���������˹��ڴ������ڣ���Ϣѭ���Ⱥ��������Ҫ��API�����н���ĳ���Ļ�������Ҫ�õ����ͷ�ļ���
/*ͷ�ļ���������*/

/*����һ���ṹ��*/
typedef struct card
{
    const char *number; // �����ַ���ָ�����number ��
    const char *color;  // �����ַ���ָ�����color ��
} Card;
// ������һ��card�Ľṹ�� ��
/*�ṹ�嶨�����*/

/*����������ʼ*/
// �������ַ�������Card�ṹ��ĺ���
void FillDeck(Card *wDeck, const char *wNumber[], const char *wColor[]);
// ����ϴ�Ƶĺ���
void Shuffle(Card *wDeck);
// �������Ƶĺ���
void Deal(Card *wDeck);
// ����д���ļ��ĺ���
void Write_File(Card *wDeck);
// ���������ļ��ĺ���
void Read_File();
// ������ӡ����
void Print();
void park();
/*������������*/

/*main������ʼ*/
int main()
{
    Print();                                                                                   // ��ӡ��ҳ��
    Card deck[52];                                                                             // ����Card������deck[]�����ڴ洢52���ƣ�
    const char *number[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}; // ָ������ĳ�ʼ������ʾ13����
    // const char *color[] = {"3", "4", "5", "6"};                                                // ָ������ĳ�ʼ������ʾ��ͬ��ɫ��
    const char *color[] = {"3", "4", "5", "6"}; // ָ������ĳ�ʼ������ʾ��ͬ��ɫ��

    FillDeck(deck, number, color); // ���ַ�������Card�ṹ��
    Shuffle(deck);                 // ϴ��
    Deal(deck);                    // ����
    Write_File(deck);              // д���ļ�
    Read_File();                   // �����ļ�
    return 0;
}
/*main��������*/

/*Print������ʼ*/
void Print() // ��ӡ��ҳ��
{
    printf("\t_________________ϵͳ���ڼ����У����Ե�_____________________\t\n\n");
    for (int i = 0; i < 20; i++)
    {
        printf(".....");
        Sleep(20); // ��ʱ��ӡ ��
    }
    system("CLS");      // ���� ��
    system("color 5F"); // ��ɫ����������ʮ����������ָ�� �� 5 = ��ɫ������ɫ�� F = ����ɫ��ǰ��ɫ����

    printf("    **********************************************************************\n");
    Sleep(10);
    printf("    * A%c      *   |   * A%c      *   |   * A%c      *   |   * A%c      *\n", 3, 4, 5, 6); // ����ASCII���,ʮ���Ƶ�3�����ַ���ʾһ�����ģ�
    Sleep(20);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    Sleep(25);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    Sleep(10);
    printf("    *         *   |   *         *   |   *         *   |   *         *\n");
    printf("    *       A%c*   |   *       A%c*   |   *       A%c*   |   *       A%c*\n", 3, 4, 5, 6);
    Sleep(10);
    printf("    **********************************************************************\n");
    Sleep(10);
    printf("    ********************************ģ�ⷢ��******************************\n");
    printf("\n");
    printf("\n");
    printf("\n");
}
/*Print��������*/

void FillDeck(Card *wDeck, const char *wNumber[], const char *wColor[])
{
    for (int i = 0; i < 52; i++)
    {
        wDeck[i].number = wNumber[i % 13];
        wDeck[i].color = wColor[i / 13];
    }
}

void Shuffle(Card *wDeck)
{
    for (int i = 0; i < 52; i++)
    {
        int j = rand() % 52;
        Card temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void Deal(Card *wDeck)
{
    for (int i = 0; i < 52; i++)
    {
        switch (i)
        {
        case 0:
            printf("\n��һ����: ");
            break;
        case 13:
            printf("\n�ڶ�����: ");
            break;
        case 26:
            printf("\n��������: ");
            break;
        case 39:
            printf("\n���ĸ���: ");
            break;
        }
        printf("%s%s\t", wDeck[i].color, wDeck[i].number);
    }
}

void Write_File(Card *wDeck)
{

    FILE *fp = NULL;              // ����һ���ļ�ָ��
    fp = fopen("data.dat", "wb"); // д��һ��dat�ļ����������ļ�
    if (fp == NULL)               // �ж��Ƿ���Դ�
    {
        printf("error!");
        return;
    }

    // д���ļ�
    for (int i = 0; i < 52; i++)
    {
        fwrite(&wDeck[i], sizeof(Card), 1, fp);
    }
    fclose(fp); // �ر��ļ�

    printf("\n\n=================================�� �� �� �� !=================================\n\n\n");
}

void Read_File()
{
    char reply; // ����һ���ַ�����������ʾ�Ƿ������Ϸ;
    int i, a;   // ����ֲ�����i(����ѭ��),a(ѡ��);

    do
    {
        Card wDeck[52];
        Card *pointer;   // ����һ�� Card�͵�ָ��pointer��
        pointer = wDeck; // �� pointerָ�� wDeck��

        FILE *fp = NULL;              // �����ļ�ָ�룻
        fp = fopen("data.dat", "rb"); // ���ļ���Ĭ�ϵ�ַ��ִ���ļ��� ��
        if (fp == NULL)
        {
            printf("error!");
            return;
        }

        // ��ȡ�ļ�
        for (int i = 0; i < 52; i++)
        {
            fread(&wDeck[i], sizeof(Card), 1, fp);
        }
        fclose(fp); // �ر�ָ�룻
        printf("\n");
        printf("�������뿴�ڼ����ƣ�1--4����");
        scanf("%d", &a);
        getchar();
        // ����a��ֵ���������Ϣ
        int offset = 0;
        switch (a)
        {
        case 1:
            printf("��һ����: ");
            offset = 0;
            break;
        case 2:
            printf("�ڶ�����: ");
            offset = 13;
            break;
        case 3:
            printf("��������: ");
            offset = 26;
            break;
        case 4:
            printf("���ĸ���: ");
            offset = 39;
            break;
        default:
            printf("����֮������룬��չʾ��һ����: ");
        }
        for (int i = 0; i < 13; i++)
        {
            int index = offset + i;
            printf("%s%s\t", wDeck[index].color, wDeck[index].number);
        }
        printf("\n\n");
        printf("�Ƿ����(���� Y/y �Լ���)��");
        scanf("%c", &reply);
    } while (reply == 'Y' || reply == 'y'); // ������y����ѭ��
}

void park()
{

    int i, a = 0;
    printf("        ��������ϴ����!       \n");
    while (a < 15) // ѭ��15��
    {
        // ÿ��forѭ������ÿ����ɫ������ʱ��
        for (i = 0; i < 9; i++)
            ;
        system("color a"); // A = ����ɫ
        for (i = 0; i < 9; i++)
            ;
        system("color b"); // B = ��ǳ��ɫ
        for (i = 0; i < 9; i++)
            ;
        system("color c"); // C = ����ɫ
        for (i = 0; i < 9; i++)
            ;
        system("color d"); // D = ����ɫ
        for (i = 0; i < 9; i++)
            ;
        system("color e"); // E = ����ɫ
        for (i = 0; i < 9; i++)
            ;
        system("color f"); // F = ����
        a++;
    }
    printf("\n\n\n        ϴ�ƽ���!        \n\n");
}
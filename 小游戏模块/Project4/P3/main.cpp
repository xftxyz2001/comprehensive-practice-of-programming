
/*�뽫��Ĭ���ն�Ӧ�ó��򡱸ĳɡ�Windows����̨������
 *�뽫�����޸�Ϊ���������塱
 *������
 *���������޸ķ�ʽ�����Word�ĵ�
 *����̨���նˣ����÷��������Word�ĵ�
 */
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
// #include <fstream>
#include <stdio.h>
using namespace std;
/*********************************************************************************/
typedef struct
{
    char color;
    char *num;
} Card;

char Colour[] = {(char)3, (char)4, (char)5, (char)6};
char Num[][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
/*********************************************************************************/
void color(unsigned short color_index);
void line(int t, int n, char c);
void HideCursor(bool Visible);
VOID SetPos(short int x, short int y);
void Init();
void FillEeck(Card *wDeck);
void Shuffle(Card *wDeck);
void Deal(Card *wDeck);
void Write_File(Card *wDeck);
void Read_File(Card *wDeck);
/// �������������ת������
/*********************************************************************************/

int main()
{
    srand(time(NULL));
    Init();         // ���ڳ�ʼ��
    Card card[52];  // �˿˽ṹ������
    FillEeck(card); // ��ʼ���˿���
    int i = 0, j;
    while (1)
    {
        while (!kbhit()) // kbhit()����������Ƿ��û����� ,λ��conio.h��.
        {
            Shuffle(card); // ϴ��
            Deal(card);    // ����
            cout << "��" << i + 1 << "��ϴ����";
            for (j = 0; j < i % 6; j++)
                cout << ".";
            color(121);
            cout << "\n\n\t�û���������(����ո�)ֹͣϴ��";
            Sleep(100);
            i++;
        }
        color(23);
        cout << "\n\t\t  ϴ�Ƴɹ�  ";
        Write_File(card); // д���ļ�
        Read_File(card);  // ���ļ�
    }
    // system("pause");
}

/// @brief ���ڳ�ʼ��
void Init()
{
    SetConsoleTitle("ϴ�ƽ��治Ҫ�������");
    system("mode con cols=60 lines=35");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨��׼io�ľ��
    SetConsoleScreenBufferSize(hOut, {63, 60});
    system("color 79");
    HideCursor(1);
    SetPos(2, 23); // ������һ�������������(2,23)(ע:����ԭ��Ϊ�ն����Ͻ�)
    color(23);
    cout << "��ʼ���У����Ե�";
    int t = 4;
    while (t--)
    {
        for (int i = 0; i < 10; i++)
        {
            Sleep(50);
            cout << ".";
        }
    }
    color(121);
}
/// @brief ��ʼ���˿���
/// @param wDeck �˿��ƽṹ��
void FillEeck(Card *wDeck)
{
    int i, j;
    for (i = 0; i < 52; i++)
    {
        wDeck[i].color = Colour[i / 13];
        wDeck[i].num = Num[i % 13];
    }
}
/// @brief ϴ��
/// @param wDeck �˿��ƽṹ��
void Shuffle(Card *wDeck)
{
    int i, j;
    Card temp;
    for (i = 0; i < 52; i++) // ����
    {
        j = rand() % 52;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}
/// @brief ����
/// @param wDeck �˿��ƽṹ��
void Deal(Card *wDeck)
{
    system("cls");
    system("color 79");
    int i, j;
    color(23);
    SetPos(0, 4);
    cout << "��һ����:" << endl
         << endl;
    for (i = 0; i < 13; i++)
    {
        if (wDeck[i].color == (char)3 || wDeck[i].color == (char)4)
        {
            color(116);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
        else
        {
            color(112);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
    }
    cout << endl
         << endl;
    color(23);
    cout << "�ڶ�����:" << endl
         << endl;
    for (i = 13; i < 26; i++)
    {
        if (wDeck[i].color == (char)3 || wDeck[i].color == (char)4)
        {
            color(116);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
        else
        {
            color(112);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
    }
    cout << endl
         << endl;
    color(23);
    cout << "��������:" << endl
         << endl;
    for (i = 26; i < 39; i++)
    {
        if (wDeck[i].color == (char)3 || wDeck[i].color == (char)4)
        {
            color(116);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
        else
        {
            color(112);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
    }
    cout << endl
         << endl;
    color(23);
    cout << "���ĸ���:" << endl
         << endl;
    for (i = 39; i < 52; i++)
    {
        if (wDeck[i].color == (char)3 || wDeck[i].color == (char)4)
        {
            color(116);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
        else
        {
            color(112);
            cout << wDeck[i].color << wDeck[i].num << "  ";
        }
    }
    cout << endl
         << endl;
    // color(119);
}
/// @brief �洢
/// @param wDeck �˿��ƽṹ��
void Write_File(Card *wDeck)
{
    FILE *fp = fopen("data.dat", "rb+");
    if (!(fp == NULL))
    {
        fwrite(wDeck, sizeof(Card), 52, fp);
    }
    fclose(fp);
}
/// @brief ����
/// @param wDeck �˿��ƽṹ��
void Read_File(Card *wDeck)
{
    char ch;
    int i, move;
    FILE *fp = fopen("data.dat", "rb+");
    Card *p = (Card *)malloc(52 * sizeof(Card));
    if (!(fp == NULL))
    {
        fread(p, sizeof(Card), 52, fp);
    }
    fclose(fp);
    Card *temp = (Card *)malloc(52 * sizeof(Card));

    while (1)
    {
        color(23);
        SetPos(0, 0);
        cout << "Esc�˳�\t\t��0����ϴ��\t��1,2,3,4�鿴��Ӧ��һ����" << endl
             << endl
             << endl;
    rechinput:
        ch = getch();
        if (ch == '1' || ch == '2' || ch == '3' || ch == '4')
        {
            system("cls");
            system("color 79");
            color(23);
            SetPos(0, 0);
            cout << "Esc�˳�\t\t��0����ϴ��\t��1,2,3,4�鿴��Ӧ��һ����" << endl
                 << endl
                 << endl;

            if (ch == '1') // move ָ��pƫ����
                move = 0;
            else if (ch == '2')
                move = 13;
            else if (ch == '3')
                move = 26;
            else if (ch == '4')
                move = 39;
            cout << "��" << move / 13 + 1 << "����:" << endl
                 << endl;
            for (i = 0, temp = p + move; i < 13; i++, temp++)
            {
                if (temp->color == (char)3 || temp->color == (char)4)
                {
                    color(116); // �׵׺���
                    cout << temp->color << temp->num << "  ";
                }
                else
                {
                    color(112); // �׵׺���
                    cout << temp->color << temp->num << "  ";
                }
            }
            cout << endl;
        }
        else if (ch == 27) // ֱ���˳�
        {
            SetPos(17, 23);
            color(121);
            cout << "Thanks for using!";
            Sleep(1000);
            exit(1);
        }
        else if (ch == '0') // ����ϴ��
            return;
        else
            goto rechinput;
    }
    free(temp);
    // cout << p->color;
}

/// @brief ���þֲ���ɫ
/// @param color_index ʮ������ɫֵ
void color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index); // ���������ɫ
}
/// @brief ��ӡ�ַ���
/// @param t "\t"������
/// @param n �ַ�c������
/// @param c �ַ�
void line(int t, int n, char c)
{
    int i;
    for (i = 0; i < t; i++)
        cout << '\t';
    for (i = 0; i < n; i++)
        cout << c;
    cout << endl;
}

/// @brief ���������
/// @param Visible �Ƿ�
void HideCursor(bool Visible)
{
    CONSOLE_CURSOR_INFO Cursor;
    Cursor.bVisible = !Visible;
    Cursor.dwSize = sizeof(Cursor);
    HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE); // STD_OUTPUT_HANDLE=-11��
    SetConsoleCursorInfo(Hand, &Cursor);           // ���ÿ���̨���״̬
}
/// @brief ָ�������������,ԭ��Ϊ����̨���Ͻ�
/// @param x ԭ������Ϊx��
/// @param y ԭ������Ϊy��
/// @return ��
VOID SetPos(short int x, short int y)
{ // set cursor2
    COORD pos = {x, y};
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, pos);
}

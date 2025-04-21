
/*请将“默认终端应用程序”改成“Windows控制台主机”
 *请将字体修改为“点阵字体”
 *方法：
 *点阵字体修改方式，详见Word文档
 *控制台（终端）设置方法，详见Word文档
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
/// 函数具体介绍请转到定义
/*********************************************************************************/

int main()
{
    srand(time(NULL));
    Init();         // 窗口初始化
    Card card[52];  // 扑克结构体数组
    FillEeck(card); // 初始化扑克牌
    int i = 0, j;
    while (1)
    {
        while (!kbhit()) // kbhit()函数，检测是否敲击键盘 ,位于conio.h中.
        {
            Shuffle(card); // 洗牌
            Deal(card);    // 发牌
            cout << "第" << i + 1 << "次洗牌中";
            for (j = 0; j < i % 6; j++)
                cout << ".";
            color(121);
            cout << "\n\n\t敲击主键盘区(比如空格)停止洗牌";
            Sleep(100);
            i++;
        }
        color(23);
        cout << "\n\t\t  洗牌成功  ";
        Write_File(card); // 写入文件
        Read_File(card);  // 读文件
    }
    // system("pause");
}

/// @brief 窗口初始化
void Init()
{
    SetConsoleTitle("洗牌界面不要用鼠标点击");
    system("mode con cols=60 lines=35");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台标准io的句柄
    SetConsoleScreenBufferSize(hOut, {63, 60});
    system("color 79");
    HideCursor(1);
    SetPos(2, 23); // 设置下一步输入输出坐标(2,23)(注:坐标原点为终端左上角)
    color(23);
    cout << "初始化中，请稍等";
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
/// @brief 初始化扑克牌
/// @param wDeck 扑克牌结构体
void FillEeck(Card *wDeck)
{
    int i, j;
    for (i = 0; i < 52; i++)
    {
        wDeck[i].color = Colour[i / 13];
        wDeck[i].num = Num[i % 13];
    }
}
/// @brief 洗牌
/// @param wDeck 扑克牌结构体
void Shuffle(Card *wDeck)
{
    int i, j;
    Card temp;
    for (i = 0; i < 52; i++) // 交换
    {
        j = rand() % 52;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}
/// @brief 发牌
/// @param wDeck 扑克牌结构体
void Deal(Card *wDeck)
{
    system("cls");
    system("color 79");
    int i, j;
    color(23);
    SetPos(0, 4);
    cout << "第一副牌:" << endl
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
    cout << "第二副牌:" << endl
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
    cout << "第三副牌:" << endl
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
    cout << "第四副牌:" << endl
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
/// @brief 存储
/// @param wDeck 扑克牌结构体
void Write_File(Card *wDeck)
{
    FILE *fp = fopen("data.dat", "rb+");
    if (!(fp == NULL))
    {
        fwrite(wDeck, sizeof(Card), 52, fp);
    }
    fclose(fp);
}
/// @brief 读牌
/// @param wDeck 扑克牌结构体
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
        cout << "Esc退出\t\t按0继续洗牌\t按1,2,3,4查看对应的一副牌" << endl
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
            cout << "Esc退出\t\t按0继续洗牌\t按1,2,3,4查看对应的一副牌" << endl
                 << endl
                 << endl;

            if (ch == '1') // move 指针p偏移量
                move = 0;
            else if (ch == '2')
                move = 13;
            else if (ch == '3')
                move = 26;
            else if (ch == '4')
                move = 39;
            cout << "第" << move / 13 + 1 << "副牌:" << endl
                 << endl;
            for (i = 0, temp = p + move; i < 13; i++, temp++)
            {
                if (temp->color == (char)3 || temp->color == (char)4)
                {
                    color(116); // 白底红字
                    cout << temp->color << temp->num << "  ";
                }
                else
                {
                    color(112); // 白底黑字
                    cout << temp->color << temp->num << "  ";
                }
            }
            cout << endl;
        }
        else if (ch == 27) // 直接退出
        {
            SetPos(17, 23);
            color(121);
            cout << "Thanks for using!";
            Sleep(1000);
            exit(1);
        }
        else if (ch == '0') // 返回洗牌
            return;
        else
            goto rechinput;
    }
    free(temp);
    // cout << p->color;
}

/// @brief 设置局部颜色
/// @param color_index 十进制颜色值
void color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index); // 设置输出颜色
}
/// @brief 打印字符串
/// @param t "\t"的数量
/// @param n 字符c的数量
/// @param c 字符
void line(int t, int n, char c)
{
    int i;
    for (i = 0; i < t; i++)
        cout << '\t';
    for (i = 0; i < n; i++)
        cout << c;
    cout << endl;
}

/// @brief 隐藏鼠标光标
/// @param Visible 是否
void HideCursor(bool Visible)
{
    CONSOLE_CURSOR_INFO Cursor;
    Cursor.bVisible = !Visible;
    Cursor.dwSize = sizeof(Cursor);
    HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE); // STD_OUTPUT_HANDLE=-11；
    SetConsoleCursorInfo(Hand, &Cursor);           // 设置控制台光标状态
}
/// @brief 指定文字输出坐标,原点为控制台左上角
/// @param x 原点以右为x轴
/// @param y 原点以下为y轴
/// @return 无
VOID SetPos(short int x, short int y)
{ // set cursor2
    COORD pos = {x, y};
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, pos);
}

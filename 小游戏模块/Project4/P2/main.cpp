#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* 定义扑克牌结构体 */
typedef struct card {
    const char *number; // 牌面值
    const char *color;  // 花色（内部用"3","4","5","6"表示）
} Card;

/* 函数声明 */
void FillDeck(Card *wDeck, const char *wNumber[], const char *wColor[]);
void Shuffle(Card *wDeck);
void Deal(Card *wDeck);
void Write_File(Card *wDeck);
void Read_File();
void Print();
void park();

int main() {
    Print(); // 打印首页面
    Card deck[52]; // 定义Card型数组deck[]，用于存储52张牌
   
    const char *number[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char *color[] = {"3", "4", "5", "6"}; // 3:红心,4:方块,5:梅花,6:黑桃
    
    FillDeck(deck, number, color); //将字符串放入Card结构体
    Shuffle(deck); //洗牌
    Deal(deck); //发牌
    Write_File(deck); //写入文件
    Read_File(); //读出文件
    
    return 0;
}

void Print() {
    printf("\t_______________________系统正在加载中，请稍等________________________\t\n\n");
    for(int i=0;i<20;i++) {
        printf(".....");
        Sleep(200);
    }
    system("CLS");
    system("color 5F");
    
    printf("********************************************************************\n");
    Sleep(100);
    printf(" * A? * | * A? * | * A? * | * A? *\n");
    Sleep(200);
    printf(" *   * | *   * | *   * | *   *\n");
    printf(" *   * | *   * | *   * | *   *\n");
    Sleep(250);
    printf(" *   * | *   * | *   * | *   *\n");
    Sleep(100);
    printf(" *   * | *   * | *   * | *   *\n");
    printf(" * A?* | * A?* | * A?* | * A?*\n");
    Sleep(100);
    printf("********************************************************************\n");
    Sleep(100);
    printf("***************************模拟发牌*******************************\n");
    printf("\n\n\n");
}

void FillDeck(Card *wDeck, const char *wNumber[], const char *wColor[]) {
    int i = 0;
    for (int c = 0; c < 4; c++) {
        for (int n = 0; n < 13; n++) {
            wDeck[i].color = wColor[c];
            wDeck[i].number = wNumber[n];
            i++;
        }
    }
}

void Shuffle(Card *wDeck) {
    park();
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        Card temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void Deal(Card *wDeck) {
    printf("\n\n=======================发牌结果=======================\n");
    
    for (int i = 0; i < 52; i++) {
        // 直接输出花色符号
         
        printf("%s%c ", wDeck[i].number, *wDeck[i].color);
        if ((i + 1) % 13 == 0) printf("\n");
    }
    printf("===================================================\n");
}

void Write_File(Card *wDeck) {
    FILE *fp = NULL;
    fp = fopen("data.dat", "wb");
    if (fp == NULL) {
        printf("无法创建文件！\n");
        return;
    }
    
    // 将牌组写入文件
    for (int i = 0; i < 52; i++) {
        if(fwrite(&wDeck[i], sizeof(Card), 1, fp) != 1) {
            printf("写入文件出错！\n");
            break;
        }
    }
    
    fclose(fp);
    printf("\n\n=================================存储成功!=================================\n\n\n");
}

void Read_File() {
    char reply;
    int i, a;
    
    do {
        Card wDeck[52];
        
        FILE *fp = NULL;
        fp = fopen("data.dat", "rb");
        if (fp == NULL) {
            printf("无法读取文件！\n");
            return;
        }
        
        // 从文件读取牌组
        for (i = 0; i < 52; i++) {
            if(fread(&wDeck[i], sizeof(Card), 1, fp) != 1) {
                printf("读取文件出错！\n");
                break;
            }
        }
        
        fclose(fp);
        
        printf("\n请问您想看第几副牌（1-4）：");
        scanf("%d", &a);
        getchar(); // 吸收回车
        
        if (a >= 1 && a <= 4) {
            printf("\n第%d副牌：\n", a);
            for (i = (a-1)*13; i < a*13; i++) {
                printf("%s%c ", wDeck[i].number, *wDeck[i].color);
            }
            printf("\n");
        } else {
            printf("输入错误！\n");
        }
        
        printf("是否继续查看(Y/N)：");
        scanf("%c", &reply);
    } while (reply == 'Y' || reply == 'y');
}

void park() {
    int i, a = 0;
    printf(" 华丽丽的洗牌中! \n");
    
    while (a < 15) {
        for (i = 0; i < 9; i++);
        system("color a");
        for (i = 0; i < 9; i++);
        system("color b");
        for (i = 0; i < 9; i++);
        system("color c");
        for (i = 0; i < 9; i++);
        system("color d");
        for (i = 0; i < 9; i++);
        system("color e");
        for (i = 0; i < 9; i++);
        system("color f");
        a++;}
        printf("\n\n\n 洗牌结束！\n\n");}

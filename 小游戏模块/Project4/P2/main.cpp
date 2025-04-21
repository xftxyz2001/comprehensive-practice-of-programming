#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* �����˿��ƽṹ�� */
typedef struct card {
    const char *number; // ����ֵ
    const char *color;  // ��ɫ���ڲ���"3","4","5","6"��ʾ��
} Card;

/* �������� */
void FillDeck(Card *wDeck, const char *wNumber[], const char *wColor[]);
void Shuffle(Card *wDeck);
void Deal(Card *wDeck);
void Write_File(Card *wDeck);
void Read_File();
void Print();
void park();

int main() {
    Print(); // ��ӡ��ҳ��
    Card deck[52]; // ����Card������deck[]�����ڴ洢52����
   
    const char *number[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char *color[] = {"3", "4", "5", "6"}; // 3:����,4:����,5:÷��,6:����
    
    FillDeck(deck, number, color); //���ַ�������Card�ṹ��
    Shuffle(deck); //ϴ��
    Deal(deck); //����
    Write_File(deck); //д���ļ�
    Read_File(); //�����ļ�
    
    return 0;
}

void Print() {
    printf("\t_______________________ϵͳ���ڼ����У����Ե�________________________\t\n\n");
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
    printf("***************************ģ�ⷢ��*******************************\n");
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
    printf("\n\n=======================���ƽ��=======================\n");
    
    for (int i = 0; i < 52; i++) {
        // ֱ�������ɫ����
         
        printf("%s%c ", wDeck[i].number, *wDeck[i].color);
        if ((i + 1) % 13 == 0) printf("\n");
    }
    printf("===================================================\n");
}

void Write_File(Card *wDeck) {
    FILE *fp = NULL;
    fp = fopen("data.dat", "wb");
    if (fp == NULL) {
        printf("�޷������ļ���\n");
        return;
    }
    
    // ������д���ļ�
    for (int i = 0; i < 52; i++) {
        if(fwrite(&wDeck[i], sizeof(Card), 1, fp) != 1) {
            printf("д���ļ�����\n");
            break;
        }
    }
    
    fclose(fp);
    printf("\n\n=================================�洢�ɹ�!=================================\n\n\n");
}

void Read_File() {
    char reply;
    int i, a;
    
    do {
        Card wDeck[52];
        
        FILE *fp = NULL;
        fp = fopen("data.dat", "rb");
        if (fp == NULL) {
            printf("�޷���ȡ�ļ���\n");
            return;
        }
        
        // ���ļ���ȡ����
        for (i = 0; i < 52; i++) {
            if(fread(&wDeck[i], sizeof(Card), 1, fp) != 1) {
                printf("��ȡ�ļ�����\n");
                break;
            }
        }
        
        fclose(fp);
        
        printf("\n�������뿴�ڼ����ƣ�1-4����");
        scanf("%d", &a);
        getchar(); // ���ջس�
        
        if (a >= 1 && a <= 4) {
            printf("\n��%d���ƣ�\n", a);
            for (i = (a-1)*13; i < a*13; i++) {
                printf("%s%c ", wDeck[i].number, *wDeck[i].color);
            }
            printf("\n");
        } else {
            printf("�������\n");
        }
        
        printf("�Ƿ�����鿴(Y/N)��");
        scanf("%c", &reply);
    } while (reply == 'Y' || reply == 'y');
}

void park() {
    int i, a = 0;
    printf(" ��������ϴ����! \n");
    
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
        printf("\n\n\n ϴ�ƽ�����\n\n");}

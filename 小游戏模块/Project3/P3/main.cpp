/*ͷ�ļ�������ʼ*/
#include <stdio.h>                                 //������׼���������
#include <stdlib.h>                                //������׼�⺯��
#include <windows.h>                               //���������˹��ڴ������ڣ���Ϣѭ���Ⱥ��������Ҫ��API�����н���ĳ���Ļ�������Ҫ�õ����ͷ�ļ��� 
#include <time.h>                                  //�������ں�ʱ���ͷ�ļ���������Ҫʱ�䷽��ĺ��� ��
#include <math.h>                                  //�����˺ܶ���ѧ�����ĺ����� 
/*ͷ�ļ���������*/

/*����������ʼ*/

void MainMenu();                                  //�˵�ҳ��ģ��
void PlayerChoice();                              //ѡ��ģ��
void ExitGame();                                  //�˳�ģ��
void Magician();                                  //ħ��ʦ����ģ��
void Viewer() ;                                   //����ģ��
//int  InputFiveNumber();                            //����5������ֵ
/*������������*/

/*����ȫ�ֱ�����ʼ*/
int nHundreds;                                    //��λ
int nTens;                                        //ʮλ
int nOnes;                                        //��λ
int nSum;                                         //����� 5�����ĺ�ֵ
int nNumber;                                      //��λ����ֵ
/*����ȫ�ֱ�������*/


int main() {
	srand(time(0));
	MainMenu();                                   //�������˵�����
	return 0;
}

void MainMenu() {                                 //ϵͳ���˵�

	int nSelect1;                                   //�ֲ�������ʾѡ��
	while (1) {
		printf("-------------------------------Main Menu-------------------------------\n");
		printf("\n");
		printf("\t     1   �˳�\n");
		printf("\t     2   ������Ϸ\n");
		printf("��������Ӧ�����֣����벻ͬ��ģ��:  \n");
		printf("-----------------------------------------------------------------------\n");
		scanf("%d", &nSelect1);
		getchar();
		fflush(stdin);
		if (nSelect1 == 1) {
			ExitGame();                           //��ת���˳�ģ��
		} else if (nSelect1 == 2) {
			PlayerChoice();                        //��ת��ѡ��ģ��
		} else {
			printf("\n     ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ��\n\n\n");
		}
	}
}

void PlayerChoice() {                       //ѡ����ҵ����
	int nSelect2;                           //ѡ��ͬ��ģʽ�����벻ͬ�Ľ�ɫ
	printf("\n");
	printf("   ��ӭ������Ϸ����ѡ�����Ľ�ɫ��  \n");
	printf("\n");
	printf("        ����   1 ����ħ��ʦ \n");
	printf("        ����   2 ���ǹ���  \n");
	printf("\n��������Ӧ�����֣����벻ͬ��ģ��:  \n");
	printf("\n");
	scanf("%d", &nSelect2);
	getchar();
	if (nSelect2 == 1) {
		printf("     ��ħ��ʦ��ӭ����  \n");
		printf("\n");
		Magician();          //����ħ��ʦ�Ľ�ɫ��
	} else if (nSelect2 == 2) {
		printf("     �װ���С��顣�����ʰɣ����Ѿ�׼�����ˣ�  \n");
		printf("\n");
		Viewer();            //������ڵĽ�ɫ��
	} else {
		printf("\n      ��������أ�   ��û���Ǹ�ѡ��ò���   ��������������ٴ�ѡ�� \n");
	}
}

void ExitGame() {                                          //�˳�ģ�麯��
	char select;              //�ֲ��ַ��������ڶ���Y��N
	printf("\n ��ȷ���˳���Ϸ�� ^-^ �� �˳� ������ Y �� y , ����������� \n\n");
	scanf( "%c", &select );
	getchar();
	if (select == 'Y' || select == 'y') {
		printf("\n     ��ӭ�´�����Ŷ������    \n");
		exit(1);
	} else {
		return;
	}
}


void Magician() {
	// �����������һ����λ��
	int number = 100 + rand() % 900;
	int a = number / 100;
	int b = (number / 10) % 10;
	int c = number % 10;

	// ��������������ĺ�
	int sum = (a * 100 + c * 10 + b) + (b * 100 + a * 10 + c) +
	          (b * 100 + c * 10 + a) + (c * 100 + a * 10 + b) +
	          (c * 100 + b * 10 + a);

	printf("\n�����Ѿ������һ����λ����\n");
	printf("����������ĺ���: %d\n", sum);
	printf("���ܲ³�ԭʼ������\n");

	int guess, attempts = 0;
	do {
		printf("��Ĳ²⣨100-999��: ");
		scanf("%d", &guess);
		attempts++;

		if (guess < number) {
			printf("��С�ˣ������Կ���\n");
		} else if (guess > number) {
			printf("�´��ˣ������Կ���\n");
		}
	} while (guess != number && attempts < 5);

	if (guess == number) {
		printf("\n��ϲ�㣡�¶��ˣ�ԭʼ���־��� %d\n", number);
	} else {
		printf("\n���ź�����ȷ���� %d\n", number);
	}
	MainMenu();
}

void Viewer() {
	int number;
	int sum = 0;
	int max_attempts = 100;  // ��ֹ��ѭ��������Դ���

	printf("����������������ĺͣ����磺���ԭʼ���� 123��������������ĺ��� 123 + 132 + 213 + 231 + 312 + 321 = 1332��:\n");
	scanf("%d", &sum);

	// ħ��ʦ�����ľ�ȷ�㷨
	int nCon = sum / 222;  // ��ʼ����
	int remainder;
	int guessed_number = -1;
	int attempts = 0;  // ��¼���Դ���

	while (attempts < max_attempts) {
		remainder = nCon * 222 - sum;

		if (remainder < 100) {
			nCon++;  // ����̫С����������
		} else if (remainder > 999) {
			nCon--;  // ����̫�󣬼�������
		} else {
			// �ֽ�����Ϊ a, b, c
			int ga = remainder / 100;
			int gb = (remainder / 10) % 10;
			int gc = remainder % 10;

			if (ga + gb + gc == nCon) {
				guessed_number = remainder;
				break;  // �ҵ���
			} else {
				nCon++;  // ����������һ������
			}
		}
		attempts++;
	}

	if (guessed_number != -1) {
		printf("\n���������������......%d��\n", guessed_number);
	} else {
		printf("\n����ĺͲ��Ϸ����޷���ԭ����ȷ����λ����\n");
		printf("���������Ƿ���ȷ�����磺ԭʼ�� 123 �ĺ��� 1332����\n");
	}

	MainMenu();
}
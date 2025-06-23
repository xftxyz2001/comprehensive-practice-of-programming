#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "class.h"
#include "attendance.h"
#include "statistics.h"
#include "query.h"
#include "data.h"

void main_menu();
//void Print();

int main() {
    
    load_all_data();
    main_menu();
    save_all_data();
    return 0;
}

void main_menu() {
    int choice;
    while (1) {
        system("color 5F");

        system("CLS"); //ϵͳ��Ļ��� 
        //����˵������� 
        printf("\t\t ---------------------------- \n");
        printf("\t\t|     ��ʦ��������ϵͳ       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    1. ������Ϣ����ģ��     |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    2. �ճ�����ģ��         |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    3. ͳ�������ģ��       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    4. ��ѯ�뱨��ģ��       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    0. �˳�                 |\n");
        printf("\t\t----------------------------- \n");
        printf("\t\t   ��ѡ�������(0~4):");

        scanf_s("%d", &choice);
        switch (choice) {
            case 1: student_info_menu(); break;
            case 2: attendance_menu(); break;
            case 3: statistics_menu(); break;
            case 4: query_menu(); break;
            case 0: return;
            default: printf("\t\tѡ����������ѡ��\n");
            Sleep(1000);
        }
    }
}

//void Print() {
//
//    for (int i = 0; i < 6; i++) {
//        printf("*****");
//        Sleep(200); //��ʱ��ӡ
//    }
//    printf("\n");
//
//}
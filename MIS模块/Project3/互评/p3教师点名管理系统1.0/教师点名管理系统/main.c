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

        system("CLS"); //系统屏幕清空 
        //输出菜单主界面 
        printf("\t\t ---------------------------- \n");
        printf("\t\t|     教师点名管理系统       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    1. 基本信息管理模块     |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    2. 日常点名模块         |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    3. 统计与分析模块       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    4. 查询与报表模块       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    0. 退出                 |\n");
        printf("\t\t----------------------------- \n");
        printf("\t\t   请选择功能序号(0~4):");

        scanf_s("%d", &choice);
        switch (choice) {
            case 1: student_info_menu(); break;
            case 2: attendance_menu(); break;
            case 3: statistics_menu(); break;
            case 4: query_menu(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
            Sleep(1000);
        }
    }
}

//void Print() {
//
//    for (int i = 0; i < 6; i++) {
//        printf("*****");
//        Sleep(200); //延时打印
//    }
//    printf("\n");
//
//}
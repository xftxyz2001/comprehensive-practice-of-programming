#include "student.h"
#include <stdio.h>
#include <string.h>

// Global data
Class class_list[MAX_CLASSES];
int class_count = 0;
Student student_list[MAX_STUDENTS];
int student_count = 0;
AttendanceRecord attendance_list[MAX_ATTENDANCE];
int attendance_count = 0;

void class_management_menu();
void student_management_menu();
void attendance_record_management_menu();

// --- Class Management ---
void add_class() {
    if (class_count >= MAX_CLASSES) {
        printf("\t\t班级名单已满\n");
        return;
    }
    Class c;
    printf("输入班级 ID: ");
    scanf_s("%d", &c.id);
    printf("输入班级名字: ");
    scanf_s("%s", c.name, (unsigned)MAX_NAME_LEN);
    class_list[class_count++] = c;
    printf("班级成功添加!\n");
}

void list_classes() {
    printf("\n班级名单:\n");
    for (int i = 0; i < class_count; ++i) {
        printf("ID: %d, Name: %s\n", class_list[i].id, class_list[i].name);
    }
    if (class_count == 0) printf("No classes found.\n");
}

// --- Student Management ---
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("学生名单已满!\n");
        return;
    }
    if (class_count == 0) {
        printf("没有可用的班级 请先添加一个班级！\n");
        return;
    }
    printf("可选择的班级:\n");
    for (int i = 0; i < class_count; ++i) {
        printf("  ID: %d, Name: %s\n", class_list[i].id, class_list[i].name);
    }
    Student s;
    printf("输入学生 ID: ");
    scanf_s("%d", &s.id);
    printf("输入学生姓名: ");
    scanf_s("%s", s.name, (unsigned)MAX_NAME_LEN);
    int valid = 0;
    while (!valid) {
        printf("输入班级 ID: ");
        scanf_s("%d", &s.class_id);
        for (int i = 0; i < class_count; ++i) {
            if (class_list[i].id == s.class_id) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            printf("班级 ID 无效，请从上述班级中选择\n");
        }
    }
    student_list[student_count++] = s;
    printf("学生添加成功!\n");
}

void list_students() {
    printf("\n学生名单:\n");
    for (int i = 0; i < student_count; ++i) {
        printf("ID: %d, Name: %s, Class ID: %d\n", student_list[i].id, student_list[i].name, student_list[i].class_id);
    }
    if (student_count == 0) printf("没有一个学生.\n");
}

// --- Attendance Record Management ---
void add_attendance_record() {
    if (attendance_count >= MAX_ATTENDANCE) {
        printf("考勤记录列表已满!\n");
        return;
    }
    AttendanceRecord r;
    // Auto-generate ID
    int max_id = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (attendance_list[i].id > max_id) max_id = attendance_list[i].id;
    }
    r.id = max_id + 1;
    printf("输入学生 ID: ");
    scanf_s("%d", &r.student_id);
    printf("输入日期 (YYYY-MM-DD): ");
    scanf_s("%s", r.date, (unsigned)sizeof(r.date));
    printf("输入考勤状态 (Present/Absent/Late/Leave): ");
    scanf_s("%s", r.status, (unsigned)MAX_STATUS_LEN);
    attendance_list[attendance_count++] = r;
    printf("Attendance record added successfully!\n");
}

void list_attendance_records() {
    printf("\n考勤记录表:\n");
    for (int i = 0; i < attendance_count; ++i) {
        // Find student
        int sid = attendance_list[i].student_id;
        const char* student_name = NULL;
        int class_id = -1;
        const char* class_name = NULL;
        for (int j = 0; j < student_count; ++j) {
            if (student_list[j].id == sid) {
                student_name = student_list[j].name;
                class_id = student_list[j].class_id;
                break;
            }
        }
        if (class_id != -1) {
            for (int k = 0; k < class_count; ++k) {
                if (class_list[k].id == class_id) {
                    class_name = class_list[k].name;
                    break;
                }
            }
        }
        printf("ID: %d, Student ID: %d", attendance_list[i].id, sid);
        if (student_name) printf(", Name: %s", student_name);
        if (class_name) printf(", Class: %s", class_name);
        printf(", Date: %s, Status: %s\n", attendance_list[i].date, attendance_list[i].status);
    }
    if (attendance_count == 0) printf("未找到考勤记录.\n");
}

void student_info_menu() {
    int choice;
    while (1) {
        system("CLS");
        system(" color 0D");
        printf("\t\t -----------------------------\n");
        printf("\t\t| *****基本信息管理模块 ***** |\n");
        printf("\t\t|                             |\n");
        printf("\t\t|      1.班级信息管理         |\n");
        printf("\t\t|                             |\n");
        printf("\t\t|      2.学生信息管理         |\n");
        printf("\t\t|                             |\n");
        printf("\t\t|      3.考勤记录管理         |\n");
        printf("\t\t|                             |\n");
        printf("\t\t|      0.返回上级菜单         |\n");
        printf("\t\t|                             |\n");
        printf("\t\t ------------------------------ \n");
        printf("\t\t   请选择功能序号(0~3):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: class_management_menu(); break;
            case 2: student_management_menu(); break;
            case 3: attendance_record_management_menu(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
                Sleep(1000);
        }
    }
}

void class_management_menu() {
    int choice;
    while (1) {
       /* printf("\n--- Class Management ---\n");
        printf("1. Add Class\n");
        printf("2. List Classes\n");
        printf("0. Back\n");
        printf("Please select: ");*/

        //system("CLS");
        printf("\t\t------------------------------\n");
        printf("\t\t| *****  班级信息管理   *****|\n");
        printf("\t\t|                            |\n");
        printf("\t\t|        1.添加班级          |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|        2.班级名单          |\n");
        printf("\t\t|                            |\n");  
        printf("\t\t|        0.返回上级菜单      |\n");
        printf("\t\t|                            |\n");
        printf("\t\t   ------------------------  \n");
        printf("\t\t   请选择功能序号(0~2):");

        scanf_s("%d", &choice);
        switch (choice) {
            case 1: add_class(); break;
            case 2: list_classes(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
        }
    }
}

void student_management_menu() {
    int choice;
    while (1) {

        //system("CLS");
        printf("\t\t------------------------------\n");
        printf("\t\t| *****  学生信息管理   *****|\n");
        printf("\t\t|                            |\n");
        printf("\t\t|        1.添加学生          |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|        2.学生名单          |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|        0.返回上级菜单      |\n");
        printf("\t\t|                            |\n");
        printf("\t\t-----------------------------  \n");
        printf("\t\t   请选择功能序号(0~2):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: add_student(); break;
            case 2: list_students(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
        }
    }
}

void attendance_record_management_menu() {
    int choice;
    while (1) {
        //system("CLS");
        printf("\t\t---------------------------------\n");
        printf("\t\t| ******  考勤记录管理   ****** |\n");
        printf("\t\t|                               |\n");
        printf("\t\t|        1.添加考勤记录         |\n");
        printf("\t\t|                               |\n");
        printf("\t\t|        2.考勤记录名单         |\n");
        printf("\t\t|                               |\n");
        printf("\t\t|        0.返回上级菜单         |\n");
        printf("\t\t|                               |\n");
        printf("\t\t ------------------------------- \n");
        printf("\t\t   请选择功能序号(0~2):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: add_attendance_record(); break;
            case 2: list_attendance_records(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
        }
    }
} 
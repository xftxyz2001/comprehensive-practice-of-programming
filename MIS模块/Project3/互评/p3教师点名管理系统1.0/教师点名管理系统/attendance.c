#include "attendance.h"
#include "student.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#ifdef _WIN32
#define strcasecmp _stricmp
#endif

#ifndef _TRUNCATE
#define _TRUNCATE ((size_t)-1)
#endif

void manual_attendance() {
    if (attendance_count + student_count >= MAX_ATTENDANCE) {
        printf("没有足够的空间来存放所有出勤记录！\n");
        return;
    }
    // Get today's date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[16];
    snprintf(date, sizeof(date), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf("所有学生手动考勤 %s\n", date);
    for (int i = 0; i < student_count; ++i) {
        printf("Student ID: %d, Name: %s, Class ID: %d\n", student_list[i].id, student_list[i].name, student_list[i].class_id);
        char status[MAX_STATUS_LEN];
        printf("Enter status (Present/Absent/Late/Leave): ");
        scanf_s("%s", status, (unsigned)MAX_STATUS_LEN);
        // Find max id for attendance record
        int max_id = 0;
        for (int j = 0; j < attendance_count; ++j) {
            if (attendance_list[j].id > max_id) max_id = attendance_list[j].id;
        }
        AttendanceRecord r;
        r.id = max_id + 1 + i;
        r.student_id = student_list[i].id;
        strncpy_s(r.date, sizeof(r.date), date, _TRUNCATE);
        strncpy_s(r.status, MAX_STATUS_LEN, status, _TRUNCATE);
        attendance_list[attendance_count++] = r;
    }
    printf("已成功添加所有学生的出勤记录!\n");
    Sleep(2000);
    system("pause");
}

void random_attendance() {
    if (student_count == 0) {
        printf("没有学生可以随机选择！\n");
        Sleep(2000);
        return;
    }
    int n;
    printf("输入要随机选择的学生人数: ");
    scanf_s("%d", &n);
    if (n <= 0) {
        printf("Number must be greater than 0!\n");
        Sleep(2000);
        return;
    }
    if (n > student_count) {
        printf("人数不能超过学生总数 (%d)!\n", student_count);
        Sleep(2000);
        return;
    }
    int indices[MAX_STUDENTS];
    for (int i = 0; i < student_count; ++i) indices[i] = i;
    srand((unsigned)time(NULL));
    // Fisher-Yates shuffle
    for (int i = student_count - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }
    // Get today's date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[16];
    snprintf(date, sizeof(date), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    int max_id = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (attendance_list[i].id > max_id) max_id = attendance_list[i].id;
    }
    printf("随机选择的学生（请输入出勤情况）:\n");
    for (int i = 0; i < n; ++i) {
        int idx = indices[i];
        printf("Student ID: %d, Name: %s, Class ID: %d\n", student_list[idx].id, student_list[idx].name, student_list[idx].class_id);
        char status[MAX_STATUS_LEN];
        printf("Enter status (Present/Absent/Late/Leave): ");
        scanf_s("%s", status, (unsigned)MAX_STATUS_LEN);
        AttendanceRecord r;
        r.id = max_id + 1 + i;
        r.student_id = student_list[idx].id;
        strncpy_s(r.date, sizeof(r.date), date, _TRUNCATE);
        strncpy_s(r.status, MAX_STATUS_LEN, status, _TRUNCATE);
        attendance_list[attendance_count++] = r;
    }
    printf("已成功添加随机选择学生的出勤记录!\n");
    Sleep(2000);
    system("pause");
    
}

int is_valid_student_id(int student_id) {
    for (int i = 0; i < student_count; ++i) {
        if (student_list[i].id == student_id) return 1;
    }
    return 0;
}

int is_valid_date(const char* date) {
    // Simple check: YYYY-MM-DD, length 10, digits and '-'
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else {
            if (date[i] < '0' || date[i] > '9') return 0;
        }
    }
    return 1;
}

int is_valid_status(const char* status) {
    return strcmp(status, "Present") == 0 || strcmp(status, "Absent") == 0 || strcmp(status, "Late") == 0 || strcmp(status, "Leave") == 0;
}

int is_abnormal_status(const char* status) {
    return strcasecmp(status, "Absent") == 0 || strcasecmp(status, "Late") == 0 || strcasecmp(status, "Leave") == 0;
}

void list_attendance_with_abnormal_mark() {
    printf("\n考勤记录列表（异常标有 *）:\n");
    for (int i = 0; i < attendance_count; ++i) {
        // Find student
        const char* student_name = NULL;
        int class_id = -1;
        const char* class_name = NULL;
        for (int j = 0; j < student_count; ++j) {
            if (student_list[j].id == attendance_list[i].student_id) {
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
        printf("ID: %d, Student ID: %d", attendance_list[i].id, attendance_list[i].student_id);
        if (student_name) printf(", Name: %s", student_name);
        if (class_name) printf(", Class: %s", class_name);
        printf(", Date: %s, Status: %s", attendance_list[i].date, attendance_list[i].status);
        if (is_abnormal_status(attendance_list[i].status)) printf(" *");
        printf("\n");
    }
    if (attendance_count == 0) printf("未找到考勤记录.\n");
    system("pause");
}

void batch_import_attendance() {
    char filename[128];
    printf("输入要导入的文件名: ");
    scanf_s("%s", filename, (unsigned)sizeof(filename));
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Failed to open file: %s\n", filename);
        Sleep(2000);
        return;
    }
    int imported = 0, skipped = 0;
    int max_id = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (attendance_list[i].id > max_id) max_id = attendance_list[i].id;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        int student_id;
        char date[32] = {0}, status[32] = {0};
        if (sscanf_s(line, "%d %31s %31s", &student_id, date, (unsigned)sizeof(date), status, (unsigned)sizeof(status)) != 3) {
            printf("Invalid format, skipped: %s", line);
            Sleep(2000);
            skipped++;
            continue;
        }
        if (!is_valid_student_id(student_id)) {
            printf("Invalid student ID %d, skipped.\n", student_id);
            Sleep(2000);
            skipped++;
            continue;
        }
        if (!is_valid_date(date)) {
            printf("Invalid date %s, skipped.\n", date);
            Sleep(2000);
            skipped++;
            continue;
        }
        if (!is_valid_status(status)) {
            printf("Invalid status %s, skipped.\n", status);
            Sleep(2000);
            skipped++;
            continue;
        }
        if (attendance_count >= MAX_ATTENDANCE) {
            printf("考勤记录列表已满，已停止导入。\n");
            Sleep(2000);
            break;
        }
        AttendanceRecord r;
        r.id = ++max_id;
        r.student_id = student_id;
        strncpy_s(r.date, sizeof(r.date), date, _TRUNCATE);
        strncpy_s(r.status, MAX_STATUS_LEN, status, _TRUNCATE);
        attendance_list[attendance_count++] = r;
        imported++;
    }
    fclose(f);
    Sleep(2000);
    printf("导入了 %d 条记录，跳过了 %d 行。\n", imported, skipped);
    Sleep(2000);
    system("pause");


}

void attendance_menu() {
    int choice;
    while (1) {
        system("color 60");

        system("CLS");
        printf("\t\t----------------------------------\n");
        printf("\t\t| *****  日常点名模块   *****    |\n");
        printf("\t\t|                                |\n");
        printf("\t\t|      1.手动点名                |\n");
        printf("\t\t|                                |\n");
        printf("\t\t|      2.随机点名                |\n");
        printf("\t\t|                                |\n");
        printf("\t\t|      3.导入考勤数据            |\n");
        printf("\t\t|                                |\n");
        printf("\t\t|      4.列出考勤记录 （异常标记)|\n");
        printf("\t\t|                                |\n");
        printf("\t\t|      0.返回上级菜单            |\n");
        printf("\t\t|                                |\n");
        printf("\t\t   ------------------------------ \n");
        printf("\t\t   请选择功能序号(0~4):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: manual_attendance(); break;
            case 2: random_attendance(); break;
            case 3: batch_import_attendance(); break;
            case 4: list_attendance_with_abnormal_mark(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
                Sleep(1000);
        }
    }
} 
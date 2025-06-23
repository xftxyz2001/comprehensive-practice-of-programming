#include "statistics.h"
#include "student.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <ctype.h>
#define strcasecmp _stricmp
#else
#include <strings.h>
#endif

void calculate_student_attendance_rate() {
    printf("\n--- 学生出勤率 ---\n");
    Sleep(2000);
    for (int i = 0; i < student_count; ++i) {
        int sid = student_list[i].id;
        int class_id = student_list[i].class_id;
        const char* class_name = NULL;
        for (int k = 0; k < class_count; ++k) {
            if (class_list[k].id == class_id) {
                class_name = class_list[k].name;
                break;
            }
        }
        int total = 0, present = 0, absent = 0, late = 0, leave = 0;
        for (int j = 0; j < attendance_count; ++j) {
            if (attendance_list[j].student_id == sid) {
                total++;
                if (strcasecmp(attendance_list[j].status, "Present") == 0) present++;
                else if (strcasecmp(attendance_list[j].status, "Absent") == 0) absent++;
                else if (strcasecmp(attendance_list[j].status, "Late") == 0) late++;
                else if (strcasecmp(attendance_list[j].status, "Leave") == 0) leave++;
            }
        }
        if (total > 0) {
            double present_rate = 100.0 * present / total;
            double absent_rate = 100.0 * absent / total;
            double late_rate = 100.0 * late / total;
            double leave_rate = 100.0 * leave / total;
            printf("Student ID: %d, Name: %s", sid, student_list[i].name);
            Sleep(1000);
            if (class_name) printf(", Class: %s", class_name);
            printf("\n");
            printf("Present: %.2f%% (%d/%d)\n", present_rate, present, total);
            Sleep(1000);
            printf("Absent: %.2f%% (%d/%d)\n", absent_rate, absent, total);
            Sleep(2000);
            printf("Late: %.2f%% (%d/%d)\n", late_rate, late, total);
            Sleep(1000);
            printf("Leave: %.2f%% (%d/%d)\n", leave_rate, leave, total);
            Sleep(1000);
            system("pause");
        } else {
            printf("Student ID: %d, Name: %s", sid, student_list[i].name);
            Sleep(1000);
            if (class_name) printf(", Class: %s", class_name);
            printf(", No attendance records.\n");
            Sleep(1000);
            system("pause");
        }
    }
}

void calculate_class_attendance_rate() {
    printf("\n--- 班级出勤率 ---\n");
    Sleep(2000);
    for (int c = 0; c < class_count; ++c) {
        int class_id = class_list[c].id;
        int total = 0, present = 0, absent = 0, late = 0, leave = 0;
        // For each student in this class
        for (int i = 0; i < student_count; ++i) {
            if (student_list[i].class_id == class_id) {
                int sid = student_list[i].id;
                for (int j = 0; j < attendance_count; ++j) {
                    if (attendance_list[j].student_id == sid) {
                        total++;
                        if (strcasecmp(attendance_list[j].status, "Present") == 0) present++;
                        else if (strcasecmp(attendance_list[j].status, "Absent") == 0) absent++;
                        else if (strcasecmp(attendance_list[j].status, "Late") == 0) late++;
                        else if (strcasecmp(attendance_list[j].status, "Leave") == 0) leave++;
                    }
                }
            }
        }
        printf("Class: %s (ID: %d)\n", class_list[c].name, class_id);
        if (total > 0) {
            double present_rate = 100.0 * present / total;
            double absent_rate = 100.0 * absent / total;
            double late_rate = 100.0 * late / total;
            double leave_rate = 100.0 * leave / total;
            printf("Present: %.2f%% (%d/%d)\n", present_rate, present, total);
            Sleep(1000);
            printf("Absent: %.2f%% (%d/%d)\n", absent_rate, absent, total);
            Sleep(1000);
            printf("Late: %.2f%% (%d/%d)\n", late_rate, late, total);
            Sleep(1000);
            printf("Leave: %.2f%% (%d/%d)\n", leave_rate, leave, total);
            Sleep(1000);
            system("pause");
        } else {
            printf("No attendance records.\n");
            system("pause");
        }
    }
}

void calculate_abnormal_attendance_statistics() {
    printf("\n--- 异常考勤统计---\n");
    Sleep(2000);
    for (int i = 0; i < student_count; ++i) {
        int sid = student_list[i].id;
        int class_id = student_list[i].class_id;
        const char* class_name = NULL;
        for (int k = 0; k < class_count; ++k) {
            if (class_list[k].id == class_id) {
                class_name = class_list[k].name;
                break;
            }
        }
        int total = 0, absent = 0, late = 0, leave = 0;
        for (int j = 0; j < attendance_count; ++j) {
            if (attendance_list[j].student_id == sid) {
                total++;
                if (strcasecmp(attendance_list[j].status, "Absent") == 0) absent++;
                else if (strcasecmp(attendance_list[j].status, "Late") == 0) late++;
                else if (strcasecmp(attendance_list[j].status, "Leave") == 0) leave++;
            }
        }
        if (total > 0) {
            double abnormal = 100.0 * (absent + late + leave) / total;
            double absent_rate = 100.0 * absent / total;
            double late_rate = 100.0 * late / total;
            double leave_rate = 100.0 * leave / total;
            printf("Student ID: %d, Name: %s", sid, student_list[i].name);
            Sleep(1000);
            if (class_name) printf(", Class: %s", class_name);
            printf("\n");
            printf("Abnormal: %.2f%% (%d/%d)\n", abnormal, absent + late + leave, total);
            Sleep(1000);
            printf("Absent: %.2f%% (%d/%d)\n", absent_rate, absent, total);
            Sleep(1000);
            printf("Late: %.2f%% (%d/%d)\n", late_rate, late, total);
            Sleep(1000);
            printf("Leave: %.2f%% (%d/%d)\n", leave_rate, leave, total);
            Sleep(1000);
            system("pause");
        } else {
            printf("Student ID: %d, Name: %s", sid, student_list[i].name);
            Sleep(1000);
            //system("pause");
            if (class_name) printf(", Class: %s", class_name);
            printf(", No attendance records.\n");
            system("pause");
        }
    }
}

void statistics_menu() {
    int choice;
    while (1) {
        system("color 1F");

        system("CLS"); 
        printf("\t\t   ------------------------  \n");
        printf("\t\t|     统计与分析模块         |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    1. 学生出勤率计算       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    2. 班级出勤率计算       |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    3. 考勤异常情况统计     |\n");
        printf("\t\t|                            |\n");
        printf("\t\t|    0. 返回上级菜单         |\n");
        printf("\t\t   ------------------------  \n");
        printf("\t\t   请选择功能序号(0~3):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: calculate_student_attendance_rate(); break;
            case 2: calculate_class_attendance_rate(); break;
            case 3: calculate_abnormal_attendance_statistics(); break;
            case 0: return;
            default: printf("\t\t选择有误，请重选！\n");
                Sleep(1000);
        }
    }
} 
#include "query.h"
#include "student.h"
#include <stdio.h>
#include <string.h>

void query_student_attendance() {
    int sid;
    printf("����ѧ�� ID ��ѯ: ");
    //Sleep(1000);
    scanf_s("%d", &sid);
    // Find student
    Student* s = NULL;
    for (int i = 0; i < student_count; ++i) {
        if (student_list[i].id == sid) {
            s = &student_list[i];
            break;
        }
    }
    if (!s) {
        printf("Student ID %d not found.\n", sid);
        Sleep(1000);
        system("pause");
        return;
    }
    // Find class name
    const char* class_name = NULL;
    for (int k = 0; k < class_count; ++k) {
        if (class_list[k].id == s->class_id) {
            class_name = class_list[k].name;
            break;
        }
    }
    printf("\n��ѧ���ĳ��ڼ�¼: %d, Name: %s", s->id, s->name);
    Sleep(1000);
    if (class_name) printf(", Class: %s\n", class_name);
    Sleep(1000);
    //system("pause");
    printf("\n");
    int found = 0;
    //system("pause");
    for (int j = 0; j < attendance_count; ++j) {
        if (attendance_list[j].student_id == sid) {
            Sleep(1000);
            printf("  Date: %s, Status: %s\n", attendance_list[j].date, attendance_list[j].status);
            found = 1;
            Sleep(1000);
        }
    }
    if (!found) {
        printf("  δ�ҵ���ѧ���ĳ��ڼ�¼��\n");
        Sleep(1000);
        system("pause");
    }
    system("pause");
}

void query_attendance_by_date() {
    char date[16];
    printf("�������ڲ�ѯ (YYYY-MM-DD): ");
    scanf_s("%s", date, (unsigned)sizeof(date));
    printf("\nAttendance records for date: %s\n", date);
    int found = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (strcmp(attendance_list[i].date, date) == 0) {
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
            printf("Student ID: %d", attendance_list[i].student_id);
            if (student_name) printf(", Name: %s", student_name);
            if (class_name) printf(", Class: %s", class_name);
            printf(", Status: %s\n", attendance_list[i].status);
            found = 1;
        }
    }
    if (!found) {
        printf(" δ�ҵ������ڵĳ��ڼ�¼.\n");
    }
}

int is_date_in_range(const char* date, const char* start, const char* end) {
    return strcmp(date, start) >= 0 && strcmp(date, end) <= 0;
}

void query_attendance_by_date_range() {
    // Show all attendance records first
    printf("\nAll attendance records:\n");
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
        printf("Date: %s, Student ID: %d", attendance_list[i].date, attendance_list[i].student_id);
        if (student_name) printf(", Name: %s", student_name);
        if (class_name) printf(", Class: %s", class_name);
        printf(", Status: %s\n", attendance_list[i].status);
    }
    if (attendance_count == 0) {
        printf("δ�ҵ����ڼ�¼.\n");
        return;
    }
    // Input date range
    char start[16], end[16];
    printf("\nEnter start date (YYYY-MM-DD): ");
    scanf_s("%s", start, (unsigned)sizeof(start));
    printf("Enter end date (YYYY-MM-DD): ");
    scanf_s("%s", end, (unsigned)sizeof(end));
    printf("\n���ڼ�¼���� %s to %s:\n", start, end);
    int found = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (is_date_in_range(attendance_list[i].date, start, end)) {
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
            printf("Date: %s, Student ID: %d", attendance_list[i].date, attendance_list[i].student_id);
            if (student_name) printf(", Name: %s", student_name);
            if (class_name) printf(", Class: %s", class_name);
            printf(", Status: %s\n", attendance_list[i].status);
            found = 1;
        }
    }
    if (!found) {
        printf("�ڴ����ڷ�Χ��δ�ҵ����ڼ�¼.\n");
    }
    //printf("111");
    system("pause");
}

void export_attendance_report() {
    // Show all attendance records first
    printf("\n���г��ڼ�¼:\n");
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
        printf("Date: %s, Student ID: %d", attendance_list[i].date, attendance_list[i].student_id);
        if (student_name) printf(", Name: %s", student_name);
        if (class_name) printf(", Class: %s", class_name);
        printf(", Status: %s\n", attendance_list[i].status);
    }
    if (attendance_count == 0) {
        printf("δ�ҵ����ڼ�¼.\n");
        return;
    }
    // Input date range
    char start[16], end[16], filename[128];
    printf("\nEnter start date (YYYY-MM-DD): ");
    scanf_s("%s", start, (unsigned)sizeof(start));
    printf("Enter end date (YYYY-MM-DD): ");
    scanf_s("%s", end, (unsigned)sizeof(end));
    printf("����Ҫ�������ļ���: ");
    scanf_s("%s", filename, (unsigned)sizeof(filename));
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    //printf("222");
    //Sleep(2000);
    int found = 0;
    for (int i = 0; i < attendance_count; ++i) {
        if (strcmp(attendance_list[i].date, start) >= 0 && strcmp(attendance_list[i].date, end) <= 0) {
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
            fprintf(f, "Date: %s, Student ID: %d", attendance_list[i].date, attendance_list[i].student_id);
            if (student_name) fprintf(f, ", Name: %s", student_name);
            if (class_name) fprintf(f, ", Class: %s", class_name);
            fprintf(f, ", Status: %s\n", attendance_list[i].status);
            found = 1;
        }
    }
    
    fclose(f);
   
    if (found) {
        printf("Attendance records exported to %s.\n", filename);
        //Sleep(2000);
        
    } else {
        printf("�ڴ����ڷ�Χ��δ�ҵ����ڼ�¼.\n");
        //Sleep(2000);
        
    }
    system("pause");
}

void query_menu() {
    int choice;
    while (1) {
        system("color F8");


        system("CLS");  
        printf("\t\t   ---------------------------  \n");
        printf("\t\t|     ��ѯ�뱨��ģ��           |\n");
        printf("\t\t|                              |\n");
        printf("\t\t|    1. ��ѯѧ�����ڼ�¼       |\n");
        printf("\t\t|                              |\n");
        printf("\t\t|    2. �����ڷ�Χ��ѯ������� |\n");
        printf("\t\t|                              |\n");
        printf("\t\t|    3. �������ڱ���           |\n");
        printf("\t\t|                              |\n");
        printf("\t\t|    0. �����ϼ��˵�           |\n");
        printf("\t\t   ---------------------------  \n");
        printf("\t\t   ��ѡ�������(0~3):");


        scanf_s("%d", &choice);
        switch (choice) {
            case 1: query_student_attendance(); break;
            case 2: query_attendance_by_date_range(); break;
            case 3: export_attendance_report(); break;
            case 0: return;
            default: printf("\t\tѡ����������ѡ��\n");
                Sleep(1000);
        }
    }
} 
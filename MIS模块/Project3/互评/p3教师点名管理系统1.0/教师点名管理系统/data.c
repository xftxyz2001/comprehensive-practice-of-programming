#include "data.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

#define CLASS_FILE "classes.txt"
#define STUDENT_FILE "students.txt"
#define ATTENDANCE_FILE "attendance.txt"

void load_all_data() {
    // Load classes
    FILE *fc = fopen(CLASS_FILE, "r");
    class_count = 0;
    if (fc) {
        while (fscanf_s(fc, "%d %s", &class_list[class_count].id, class_list[class_count].name, (unsigned)MAX_NAME_LEN) == 2) {
            class_count++;
            if (class_count >= MAX_CLASSES) break;
        }
        fclose(fc);
    }
    // Load students
    FILE *fs = fopen(STUDENT_FILE, "r");
    student_count = 0;
    if (fs) {
        while (fscanf_s(fs, "%d %s %d", &student_list[student_count].id, student_list[student_count].name, (unsigned)MAX_NAME_LEN, &student_list[student_count].class_id) == 3) {
            student_count++;
            if (student_count >= MAX_STUDENTS) break;
        }
        fclose(fs);
    }
    // Load attendance records
    FILE *fa = fopen(ATTENDANCE_FILE, "r");
    attendance_count = 0;
    if (fa) {
        while (fscanf_s(fa, "%d %d %s %s", &attendance_list[attendance_count].id, &attendance_list[attendance_count].student_id, attendance_list[attendance_count].date, (unsigned)sizeof(attendance_list[attendance_count].date), attendance_list[attendance_count].status, (unsigned)MAX_STATUS_LEN) == 4) {
            attendance_count++;
            if (attendance_count >= MAX_ATTENDANCE) break;
        }
        fclose(fa);
    }
}

void save_all_data() {
    // Save classes
    FILE *fc = fopen(CLASS_FILE, "w");
    for (int i = 0; i < class_count; ++i) {
        fprintf(fc, "%d %s\n", class_list[i].id, class_list[i].name);
    }
    if (fc) fclose(fc);
    // Save students
    FILE *fs = fopen(STUDENT_FILE, "w");
    for (int i = 0; i < student_count; ++i) {
        fprintf(fs, "%d %s %d\n", student_list[i].id, student_list[i].name, student_list[i].class_id);
    }
    if (fs) fclose(fs);
    // Save attendance records
    FILE *fa = fopen(ATTENDANCE_FILE, "w");
    for (int i = 0; i < attendance_count; ++i) {
        fprintf(fa, "%d %d %s %s\n", attendance_list[i].id, attendance_list[i].student_id, attendance_list[i].date, attendance_list[i].status);
    }
    if (fa) fclose(fa);
} 
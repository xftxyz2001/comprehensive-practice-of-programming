#ifndef STUDENT_H
#define STUDENT_H

#define MAX_CLASSES 100
#define MAX_STUDENTS 1000
#define MAX_ATTENDANCE 10000
#define MAX_NAME_LEN 32
#define MAX_STATUS_LEN 16

// Class structure
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
} Class;

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int class_id;
} Student;

// Attendance record structure
typedef struct {
    int id;
    int student_id;
    char date[16];
    char status[MAX_STATUS_LEN];
} AttendanceRecord;

extern Class class_list[MAX_CLASSES];
extern int class_count;
extern Student student_list[MAX_STUDENTS];
extern int student_count;
extern AttendanceRecord attendance_list[MAX_ATTENDANCE];
extern int attendance_count;

void student_info_menu();
void add_student();
void list_students();

#endif 
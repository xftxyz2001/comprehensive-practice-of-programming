#ifndef SCOREFUNCTION_H
#define SCOREFUNCTION_H

#define STUDENT_NUM 10

#ifndef STUDENT_STRUCT
#define STUDENT_STRUCT
typedef struct {
    int id;
    char name[11];
    float scores[3];
} Student;
#endif

int CalFailNo(Student students[], int num, int subject, const char *filename);

#endif

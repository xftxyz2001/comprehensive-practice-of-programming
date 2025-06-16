#include <stdio.h>
#include <string.h>
#include "ScoreFunction.h"

int nPassScore = 60; 

int CalFailNo(Student students[], int num, int subject, const char *filename) {
    int nPassScore = 50; 
    int count = 0;
    FILE *fp = fopen(filename, "w");
    if (!fp) return -1;

    for (int i = 0; i < num; i++) {
        if (students[i].scores[subject] < nPassScore) { 
            fprintf(fp, "%d %s %.2f\n", students[i].id, students[i].name, students[i].scores[subject]);
            count++;
        }
    }
    fclose(fp);
    return count;
}

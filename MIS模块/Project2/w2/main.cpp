// main.cpp
#include <iostream>
#include "ScoreFunction.h"

using namespace std;

int main()
{
    Student students[MAX_STUDENTS];
    int count = 0;

    readStudents("student.txt", students, count);

    for (int i = 0; i < 3; ++i)
    {
        string filename = "fail_subject" + to_string(i + 1) + ".txt";
        int fail = CalFailNo(students, count, i, filename.c_str());
        cout << "第 " << i + 1 << " 门课程不及格人数: " << fail << endl;
    }

    return 0;
}

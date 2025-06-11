// ScoreFunction.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "ScoreFunction.h"

using namespace std;

// 全局变量：及格线
int nPassScore = 60;

// 读取学生数据
void readStudents(const char *filename, Student stu[], int &count)
{
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "无法打开文件 " << filename << endl;
        return;
    }

    count = 0;
    while (count < MAX_STUDENTS && fin >> stu[count].id >> stu[count].name >> stu[count].scores[0] >> stu[count].scores[1] >> stu[count].scores[2])
    {
        count++;
    }

    fin.close();
}

// 统计不及格人数并写入文件
int CalFailNo(Student stu[], int count, int subjectIndex, const char *outFilename)
{
    int nPassScore = 50; // 局部变量
    int failCount = 0;
    ofstream fout(outFilename);

    if (!fout)
    {
        cerr << "无法写入文件 " << outFilename << endl;
        return 0;
    }

    fout << "学号\t姓名\t成绩\n";
    for (int i = 0; i < count; ++i)
    {
        // if (stu[i].scores[subjectIndex] < ::nPassScore) // 强制使用全局变量
        if (stu[i].scores[subjectIndex] < nPassScore) // 默认使用局部变量
        {
            fout << stu[i].id << "\t" << stu[i].name << "\t"
                 << fixed << setprecision(2) << stu[i].scores[subjectIndex] << "\n";
            failCount++;
        }
    }

    fout.close();
    return failCount;
}

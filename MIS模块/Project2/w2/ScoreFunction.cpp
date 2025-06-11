// ScoreFunction.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "ScoreFunction.h"

using namespace std;

// ȫ�ֱ�����������
int nPassScore = 60;

// ��ȡѧ������
void readStudents(const char *filename, Student stu[], int &count)
{
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "�޷����ļ� " << filename << endl;
        return;
    }

    count = 0;
    while (count < MAX_STUDENTS && fin >> stu[count].id >> stu[count].name >> stu[count].scores[0] >> stu[count].scores[1] >> stu[count].scores[2])
    {
        count++;
    }

    fin.close();
}

// ͳ�Ʋ�����������д���ļ�
int CalFailNo(Student stu[], int count, int subjectIndex, const char *outFilename)
{
    int nPassScore = 50; // �ֲ�����
    int failCount = 0;
    ofstream fout(outFilename);

    if (!fout)
    {
        cerr << "�޷�д���ļ� " << outFilename << endl;
        return 0;
    }

    fout << "ѧ��\t����\t�ɼ�\n";
    for (int i = 0; i < count; ++i)
    {
        // if (stu[i].scores[subjectIndex] < ::nPassScore) // ǿ��ʹ��ȫ�ֱ���
        if (stu[i].scores[subjectIndex] < nPassScore) // Ĭ��ʹ�þֲ�����
        {
            fout << stu[i].id << "\t" << stu[i].name << "\t"
                 << fixed << setprecision(2) << stu[i].scores[subjectIndex] << "\n";
            failCount++;
        }
    }

    fout.close();
    return failCount;
}

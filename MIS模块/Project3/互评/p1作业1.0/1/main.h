#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define PASS 6
#define NAME 20
#define DEFAULT_SZ 2
#define DATA_FILE "users.txt"


typedef struct
{
	int id;
	char name[NAME];
	char password[PASS]; // ����
} User;
//ͨѶ¼����
typedef struct
{
	User* data;//��Ÿ�����Ϣ
	int size;//��¼ͨѶ¼����
	int capacity;//��¼ͨѶ¼��С
}Userlist;

//main ��������
//ģ��1���õ��ĺ�������
void initSystem(Userlist* ps);    // ��¼ϵͳ
void Loadsystem(Userlist* ps); // ����
void userLogin(Userlist* ps); // �û���¼
void userRegister(Userlist* ps); // �û�ע��
void saveData(Userlist* ps); // ��������
void studentMenu(int studentId); // ѧ���˵�


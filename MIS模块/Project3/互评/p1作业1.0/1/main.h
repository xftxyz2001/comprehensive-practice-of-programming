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
	char password[PASS]; // 密码
} User;
//通讯录类型
typedef struct
{
	User* data;//存放个人信息
	int size;//记录通讯录人数
	int capacity;//记录通讯录大小
}Userlist;

//main 函数声明
//模块1所用到的函数声明
void initSystem(Userlist* ps);    // 登录系统
void Loadsystem(Userlist* ps); // 加载
void userLogin(Userlist* ps); // 用户登录
void userRegister(Userlist* ps); // 用户注册
void saveData(Userlist* ps); // 保存数据
void studentMenu(int studentId); // 学生菜单


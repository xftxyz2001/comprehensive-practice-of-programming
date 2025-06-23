#ifndef MANAGER_H
#define MANAGER_H

#include "main.h"

#define NAME 50
#define PASS 20
#define MAX_USERS 100
#define MAX_DISHES 200

// 菜品结构体
typedef struct {
    char id[10];
    char name[30];
    float price;
    char type[20];
    char merchantId[5];
} Dish;

// 全局数据结构
extern User users[MAX_USERS];
extern Dish dishes[MAX_DISHES];
extern int user_count;
extern int dish_count;

// 文件操作
void loadUsers(const char* filename);
void saveUsers(const char* filename);
void loadDishesForMerchant(int merchantId);
void saveDishesForMerchant(int merchantId);

// 信息显示
void displayAllUsers();
void displayAllDishes();

// 数据删除
void deleteUser(int id);
void deleteDish(const char* id);

// 系统管理
void showMainMenu();

#endif // MANAGER_H

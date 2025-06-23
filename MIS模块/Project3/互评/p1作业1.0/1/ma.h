#ifndef MANAGER_H
#define MANAGER_H

#include "main.h"

#define NAME 50
#define PASS 20
#define MAX_USERS 100
#define MAX_DISHES 200

// ��Ʒ�ṹ��
typedef struct {
    char id[10];
    char name[30];
    float price;
    char type[20];
    char merchantId[5];
} Dish;

// ȫ�����ݽṹ
extern User users[MAX_USERS];
extern Dish dishes[MAX_DISHES];
extern int user_count;
extern int dish_count;

// �ļ�����
void loadUsers(const char* filename);
void saveUsers(const char* filename);
void loadDishesForMerchant(int merchantId);
void saveDishesForMerchant(int merchantId);

// ��Ϣ��ʾ
void displayAllUsers();
void displayAllDishes();

// ����ɾ��
void deleteUser(int id);
void deleteDish(const char* id);

// ϵͳ����
void showMainMenu();

#endif // MANAGER_H

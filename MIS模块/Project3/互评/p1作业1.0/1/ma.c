#include "ma.h"
// 全局数据结构
User users[MAX_USERS];
Dish dishes[MAX_DISHES];
int user_count = 0;
int dish_count = 0;

// 加载用户信息
void loadUsers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开用户文件 '%s'，请检查文件是否存在。\n", filename);
        return;
    }

    user_count = 0;
    char line[256];
    int line_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        if (line[0] == '\n' || line[0] == '#') continue;
        line[strcspn(line, "\n")] = 0;

        int id;
        char name[NAME], password[PASS];
        if (sscanf(line, "%d %s %s", &id, name, password) == 3) {
            if (user_count < MAX_USERS) {
                users[user_count].id = id;
                strcpy(users[user_count].name, name);
                strcpy(users[user_count].password, password);
                user_count++;
            }
            else {
                printf("警告: 达到用户数量上限，停止加载。\n");
                break;
            }
        }
        else {
            printf("错误: 用户文件第%d行格式错误: %s\n", line_num, line);
        }
    }
    fclose(file);
    printf("成功加载 %d 条用户信息。\n", user_count);
}

// 保存用户信息
void saveUsers(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法打开用户文件 '%s'!\n", filename);
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%d %s %s\n",
            users[i].id,
            users[i].name,
            users[i].password);
    }
    fclose(file);
    printf("用户信息已保存到 %s\n", filename);
}

// 加载菜品信息
void loadDishesForMerchant(int merchantId) {
    char filename[50];
    sprintf(filename, "merchant_%d_dishes.txt", merchantId);
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开菜品文件 '%s'，请检查文件是否存在。\n", filename);
        return;
    }

    dish_count = 0;
    char line[256];
    int line_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        if (line[0] == '\n' || line[0] == '#') continue;
        line[strcspn(line, "\n")] = 0;

        char id[10], name[30], type[20];
        float price;
        char merchantId[5];

        if (sscanf(line, "%s %s %f %s %s", id, name, &price, type, merchantId) == 5) {
            if (dish_count < MAX_DISHES) {
                strcpy(dishes[dish_count].id, id);
                strcpy(dishes[dish_count].name, name);
                dishes[dish_count].price = price;
                strcpy(dishes[dish_count].type, type);
                strcpy(dishes[dish_count].merchantId, merchantId);
                dish_count++;
            }
            else {
                printf("警告: 达到菜品数量上限，停止加载。\n");
                break;
            }
        }
        else {
            printf("错误: 菜品文件第%d行格式错误: %s\n", line_num, line);
        }
    }
    fclose(file);
    printf("成功加载 %d 条菜品信息。\n", dish_count);
}

// 保存菜品信息
void saveDishesForMerchant(int merchantId) {
    char filename[50];
    sprintf(filename, "merchant_%d_dishes.txt", merchantId);
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("无法打开菜品文件 '%s'!\n", filename);
        return;
    }

    for (int i = 0; i < dish_count; i++) {
        fprintf(file, "%s %s %.2f %s %s\n",
            dishes[i].id,
            dishes[i].name,
            dishes[i].price,
            dishes[i].type,
            dishes[i].merchantId);
    }
    fclose(file);
    printf("菜品信息已保存到 %s\n", filename);
}

// 显示所有用户信息
void displayAllUsers() {
    if (user_count == 0) {
        printf("\n当前没有用户信息。\n");
        return;
    }

    printf("\n%-10s %-20s %-20s\n", "用户ID", "用户名", "密码");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < user_count; i++) {
        printf("%-10d %-20s %-20s\n",
            users[i].id,
            users[i].name,
            users[i].password);
    }
    printf("共 %d 名用户\n", user_count);
}

// 显示所有菜品信息
void displayAllDishes() {
    if (dish_count == 0) {
        printf("\n当前没有菜品信息。\n");
        return;
    }

    printf("\n%-10s %-20s %-10s %-15s %-10s\n",
        "菜品ID", "菜品名称", "价格", "类型", "商家ID");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < dish_count; i++) {
        printf("%-10s %-20s %-10.2f %-15s %-10s\n",
            dishes[i].id,
            dishes[i].name,
            dishes[i].price,
            dishes[i].type,
            dishes[i].merchantId);
    }
    printf("共 %d 种菜品\n", dish_count);
}

// 删除用户
void deleteUser(int id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id) {
            printf("确认要删除用户 %d (%s) 吗? (y/n): ", id, users[i].name);
            char confirm;
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < user_count - 1; j++) {
                    users[j] = users[j + 1];
                }
                user_count--;
                printf("用户 %d 已删除\n", id);
                saveUsers("Users.txt");
                return;
            }
            else {
                printf("取消删除操作\n");
                return;
            }
        }
    }
    printf("未找到ID为 %d 的用户\n", id);
}

// 删除菜品
void deleteDish(const char* id) {
    for (int i = 0; i < dish_count; i++) {
        if (strcmp(dishes[i].id, id) == 0) {
            printf("确认要删除菜品 %s (%s) 吗? (y/n): ", id, dishes[i].name);
            char confirm;
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < dish_count - 1; j++) {
                    dishes[j] = dishes[j + 1];
                }
                dish_count--;
                printf("菜品 %s 已删除\n", id);
                saveDishesForMerchant(dishes[0].merchantId);
                return;
            }
            else {
                printf("取消删除操作\n");
                return;
            }
        }
    }
    printf("未找到ID为 %s 的菜品\n", id);
}

// 初始化系统
void initializeSystem() {
    loadUsers("Users.txt");
    if (user_count > 0) {
        int merchantId;
        sprintf(&merchantId, "%d", users[0].id);
        loadDishesForMerchant(merchantId);
    }

    if (user_count == 0 && dish_count == 0) {
        printf("\n警告: 没有加载到任何数据!\n");
        printf("请检查数据文件是否存在。程序退出时将保存数据。\n");
    }
}

// 清理系统
void cleanupSystem() {
    saveUsers("Users.txt");
    if (user_count > 0) {
        char merchantId[5];
        sprintf(merchantId, "%d", users[0].id);
        saveDishesForMerchant(merchantId);
    }
    printf("\n数据已保存!\n");
}

// 显示主菜单
void showMainMenu() {
    initializeSystem();
    int choice;
    int userId;
    char dishId[10];

    while (1) {
        printf("\n==== 餐饮管理系统 - 控制台版 ====\n");
        printf("1. 查看所有用户\n");
        printf("2. 查看所有菜品\n");
        printf("3. 删除用户\n");
        printf("4. 删除菜品\n");
        printf("5. 退出系统\n");
        printf("请选择操作: ");

        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新选择!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            displayAllUsers();
            break;
        case 2:
            displayAllDishes();
            break;
        case 3:
            printf("请输入要删除的用户ID: ");
            scanf("%d", &userId);
            deleteUser(userId);
            break;
        case 4:
            printf("请输入要删除的菜品ID: ");
            scanf("%s", dishId);
            deleteDish(dishId);
            break;
        case 5:
            cleanupSystem();
            return;
        default:
            printf("无效选择! 请输入1-5之间的数字\n");
        }
    }
}
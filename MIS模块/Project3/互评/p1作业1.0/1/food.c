#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "food.h"

// 从User.txt读取商家信息
static int loadMerchantsFromUser(int merchants[], char names[][50], int maxCount) {
    FILE* fp = fopen("Users.txt", "r");
    if (!fp) {
        printf("无法打开用户文件！\n");
        return -1;
    }

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) && count < maxCount) {
        // 假设User.txt中商家行格式为: 商家ID 商家名称 其他信息...
        int id;
        char name[50];

        // 解析商家ID和名称（跳过非商家行）
        if (sscanf(line, "%d %49s", &id, name) >= 2 && id >= 2000) {
            merchants[count] = id;
            strcpy(names[count], name);
            count++;
        }
    }

    fclose(fp);
    return count;
}

// 内部辅助函数：选择商家
static int select_merchant() {
    printf("\n===== 商家列表 =====\n");

    int merchants[100];
    char names[100][50];
    int count = loadMerchantsFromUser(merchants, names, 100);

    if (count <= 0) {
        printf("未找到商家数据！\n");
        return -1;
    }

    // 显示商家列表
    for (int i = 0; i < count; i++) {
        printf("%d. %s (ID:%d)\n", i + 1, names[i], merchants[i]);
    }

    // 选择商家
    int choice;
    printf("\n请选择商家(1-%d): ", count);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("无效选择！\n");
        return -1;
    }
    getchar();  // 清除输入缓冲区

    return merchants[choice - 1];
}

// 浏览菜品函数
int foodv(int studentId) {
    // 1. 从User.txt获取商家列表并选择
    int merchantId = select_merchant();
    if (merchantId < 0) return -1;

    // 2. 加载该商家菜品
    char filename[50];
    snprintf(filename, sizeof(filename), "merchant_%d_dishes.txt", merchantId);

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("该商家暂无菜品！\n");
        return -1;
    }

    // 3. 显示菜品列表
    printf("\n%-5s %-30s %-8s\n", "序号", "菜品名称", "价格");
    char line[256];
    int itemCount = 0;

    while (fgets(line, sizeof(line), fp) && itemCount < MAX_FOODS) {
        char id[ID_LEN], name[NAME_LEN];
        float price;
        int fileMerchantId; // 用于接收文件中的商家ID

        // 解析文件行，格式：菜品ID 菜品名称 价格 商家ID
        if (sscanf(line, "%9s %29s %f %d", id, name, &price, &fileMerchantId) == 4) {
            // 验证商家ID匹配
            if (fileMerchantId == merchantId) {
                printf("%-5d %-30s ¥%-8.2f\n", ++itemCount, name, price);
            }
        }
    }

    fclose(fp);

    // 4. 查看详情（可选）
    if (itemCount > 0) {
        printf("\n输入菜品序号查看详情(0返回): ");
        int choice;
        if (scanf("%d", &choice) == 1 && choice > 0 && choice <= itemCount) {
            printf("已选择菜品 %d\n", choice);
            // 这里可以添加菜品详情查看逻辑
        }
        getchar();
    }

    return 0;
}
#include "main.h"
#include "dish.h"
#include <errno.h>  // 用于错误处理

// 生成商家专属文件名
char* getMerchantFileName(int merchantId) {
    static char fileName[50];
    if (snprintf(fileName, sizeof(fileName), "merchant_%d_dishes.txt", merchantId) < 0) {
        perror("生成文件名失败");
        fileName[0] = '\0'; // 返回空字符串
    }
    return fileName;
}

// 菜品修改函数（接收商家ID作为参数）
void DishModify(int merchantId) {
    FILE* fp = NULL, * temp = NULL;
    char line[256];
    char id[10], inputId[10], name[30], newName[30];
    float price, newPrice;
    int choice, found = 0;
    char* fileName = getMerchantFileName(merchantId);

    if (fileName[0] == '\0') {
        return; // 文件名生成失败
    }

    printf("\n--- 菜品信息管理 ---\n");
    printf("1. 添加菜品\n");
    printf("2. 删除菜品\n");
    printf("3. 修改菜品\n");
    printf("请输入操作编号: ");
    if (scanf("%d", &choice) != 1) {
        printf("输入无效\n");
        while (getchar() != '\n'); // 清除输入缓冲区
        return;
    }
    getchar();  // 清除输入缓冲区

    switch (choice) {
    case 1:  // 添加菜品
        printf("请输入菜品编号: ");
        if (scanf("%9s", id) != 1) {
            printf("菜品编号输入无效\n");
            break;
        }
        printf("请输入菜品名称: ");
        if (scanf("%29s", name) != 1) {
            printf("菜品名称输入无效\n");
            break;
        }
        printf("请输入菜品价格: ");
        if (scanf("%f", &price) != 1) {
            printf("价格输入无效\n");
            break;
        }

        fp = fopen(fileName, "a");
        if (fp == NULL) {
            perror("无法打开文件");
            break;
        }
        if (fprintf(fp, "%s %s %.2f %d\n", id, name, price, merchantId) < 0) {
            perror("写入文件失败");
        }
        else {
            printf("添加成功\n");
        }
        if (fclose(fp) != 0) {
            perror("关闭文件失败");
        }
        break;

    case 2:  // 删除菜品
        printf("请输入要删除的菜品编号: ");
        if (scanf("%9s", inputId) != 1) {
            printf("菜品编号输入无效\n");
            break;
        }

        fp = fopen(fileName, "r");
        if (fp == NULL) {
            perror("无法打开源文件");
            break;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            perror("无法创建临时文件");
            fclose(fp);
            break;
        }

        found = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (sscanf(line, "%9s %29s %f %d", id, name, &price, &merchantId) != 4) {
                continue; // 跳过格式错误的行
            }
            if (strcmp(inputId, id) == 0) {
                found = 1;
                continue;  // 跳过当前行，即删除
            }
            if (fputs(line, temp) == EOF) {
                perror("写入临时文件失败");
                break;
            }
        }

        if (fclose(fp) != 0) {
            perror("关闭源文件失败");
        }
        if (fclose(temp) != 0) {
            perror("关闭临时文件失败");
        }

        if (found) {
            if (remove(fileName) != 0) {
                perror("删除原文件失败");
            }
            else if (rename("temp.txt", fileName) != 0) {
                perror("重命名文件失败");
            }
            else {
                printf("删除成功\n");
            }
        }
        else {
            if (remove("temp.txt") != 0) {
                perror("删除临时文件失败");
            }
            printf("未找到该菜品\n");
        }
        break;

    case 3:  // 修改菜品
        printf("请输入要修改的菜品编号: ");
        if (scanf("%9s", inputId) != 1) {
            printf("菜品编号输入无效\n");
            break;
        }

        fp = fopen(fileName, "r");
        if (fp == NULL) {
            perror("无法打开源文件");
            break;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            perror("无法创建临时文件");
            fclose(fp);
            break;
        }

        found = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (sscanf(line, "%9s %29s %f %d", id, name, &price, &merchantId) != 4) {
                if (fputs(line, temp) == EOF) {
                    perror("写入临时文件失败");
                }
                continue;
            }
            if (strcmp(inputId, id) == 0) {
                found = 1;
                printf("当前菜品: %s %s %.2f\n", id, name, price);
                printf("请输入新名称: ");
                if (scanf("%29s", newName) != 1) {
                    printf("名称输入无效\n");
                    fputs(line, temp); // 保留原数据
                    continue;
                }
                printf("请输入新价格: ");
                if (scanf("%f", &newPrice) != 1) {
                    printf("价格输入无效\n");
                    fputs(line, temp); // 保留原数据
                    continue;
                }
                if (fprintf(temp, "%s %s %.2f %d\n", id, newName, newPrice, merchantId) < 0) {
                    perror("写入临时文件失败");
                }
            }
            else {
                if (fputs(line, temp) == EOF) {
                    perror("写入临时文件失败");
                }
            }
        }

        if (fclose(fp) != 0) {
            perror("关闭源文件失败");
        }
        if (fclose(temp) != 0) {
            perror("关闭临时文件失败");
        }

        if (found) {
            if (remove(fileName) != 0) {
                perror("删除原文件失败");
            }
            else if (rename("temp.txt", fileName) != 0) {
                perror("重命名文件失败");
            }
            else {
                printf("修改成功\n");
            }
        }
        else {
            if (remove("temp.txt") != 0) {
                perror("删除临时文件失败");
            }
            printf("未找到该菜品\n");
        }
        break;

    default:
        printf("无效选择\n");
    }
}
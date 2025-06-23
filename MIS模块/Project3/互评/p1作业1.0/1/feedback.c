#include "main.h"
#include "stu.h"
#include "food.h"
#include "dish.h"

Feedback feedbacks[MAX_FEEDBACKS];
int feedbackCount = 0;

// 获取当前时间（仅添加返回值检查）
char* getCurrentTime() {
    static char timeStr[20] = ""; // 确保有默认值
    time_t now;
    struct tm* timeinfo;

    time(&now); // 保持原样，不检查返回值
    timeinfo = localtime(&now); // 保持原样
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", timeinfo); // 保持原样

    return timeStr;
}

// 商家菜单（仅添加输入检查）
void merchantMenu(int merchantId) {
    loadAllData(); // 保持原样
    int n;
    do {
        printf("\n===== 商家菜单 =====\n");
        printf("1. 产品预览\n");
        printf("2. 产品修改\n");
        printf("3. 查看反馈\n");
        printf("0. 退出\n");
        printf("请选择: ");

        if (scanf("%d", &n) != 1) { // 仅添加输入检查
            n = -1; // 保持原有错误处理流程
        }

        while (getchar() != '\n'); // 保持原样

        switch (n) { // 原有逻辑完全不变
        case 1: foodv(merchantId); break;
        case 2: DishModify(merchantId); break;
        case 3: marchantFeedback(merchantId); break;
        case 0: printf("退出商家菜单...\n"); break;
        default: printf("无效选择，请重新输入！\n");
        }
    } while (n != 0);
    saveAllData(); // 保持原样
}

// 查看商家反馈（仅添加输入检查）
void marchantFeedback(int merchantId) {
    printf("\n===== 商家反馈信息 =====\n");
    printf("商家编号: %d\n", merchantId);
    printf("========================\n");

    int found = 0;
    for (int i = 0; i < feedbackCount; i++) {
        if (feedbacks[i].merchantId == merchantId) {
            printf("\n反馈编号: %d\n", feedbacks[i].id);
            printf("提交时间: %s\n", feedbacks[i].time);
            printf("反馈问题: %s\n", feedbacks[i].problem);
            printf("回复内容: %s\n", feedbacks[i].reply);
            printf("------------------------\n");
            found = 1;

            int choice;
            do {
                printf("\n===== 商家回复菜单 =====\n");
                printf("1. 回复\n");
                printf("0. 退出\n");
                printf("请选择: ");

                if (scanf("%d", &choice) != 1) { // 仅添加输入检查
                    choice = -1; // 保持原有错误处理
                }

                while (getchar() != '\n'); // 保持原样

                switch (choice) { // 原有逻辑完全不变
                case 1: replyToFeedback(); break;
                case 0: printf("退出商家回复菜单...\n"); break;
                default: printf("无效选择，请重新输入！\n");
                }
            } while (choice != 0);
        }
    }
    if (!found) {
        printf("暂无反馈记录！\n"); // 保持原样
    }
}

// 回复反馈（仅添加必要检查）
void replyToFeedback() {
    int feedbackId;
    printf("\n请输入要回复的反馈编号 (0返回): ");

    if (scanf("%d", &feedbackId) != 1) { // 仅添加输入检查
        feedbackId = 0; // 保持原有流程
    }
    getchar(); // 保持原样

    if (feedbackId == 0) return;

    Feedback* target = NULL;
    for (int i = 0; i < feedbackCount; i++) {
        if (feedbacks[i].id == feedbackId) {
            target = &feedbacks[i];
            break;
        }
    }

    if (!target) {
        printf("未找到该反馈！\n"); // 保持原样
        return;
    }

    printf("\n当前反馈信息:\n");
    printf("反馈问题: %s\n", target->problem);
    printf("当前回复: %s\n", target->reply);

    printf("\n请输入回复内容: ");
    char newReply[150];
    if (fgets(newReply, sizeof(newReply), stdin) == NULL) { // 仅添加检查
        newReply[0] = '\0'; // 保持原有流程
    }
    newReply[strcspn(newReply, "\n")] = '\0'; // 保持原样

    if (strlen(newReply) > 0) { // 原有逻辑完全不变
        strncpy(target->reply, newReply, sizeof(target->reply));
        target->reply[sizeof(target->reply) - 1] = '\0'; // 确保终止符

        // 保持原有时间更新逻辑
        char* timeStr = getCurrentTime();
        strncpy(target->time, timeStr, sizeof(target->time));
        target->time[sizeof(target->time) - 1] = '\0';

        saveAllData(); // 保持原样
        printf("回复已更新！\n");
    }
    else {
        printf("回复内容不能为空！\n"); // 保持原样
    }
}
#include "main.h"
#include "stu.h"
#include "food.h"

// 学生菜单
void studentMenu(int studentId) {
    loadAllData(); // 加载所有数据

    int choice;
    do {
        printf("\n===== 学生菜单 =====\n");
        printf("1. 产品预览\n");
        printf("2. 提交反馈\n");
        printf("3. 查看我的反馈\n");
        printf("0. 退出\n");
        printf("请选择: ");

        // 处理无效输入
        while (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新输入选择: ");
            while (getchar() != '\n'); // 清空输入缓冲区
        }
        while (getchar() != '\n'); // 清除剩余字符

        switch (choice) {
        case 1:
            foodv(studentId);
            break;
        case 2:
            studentFeedback(studentId);
            break;
        case 3:
            displayStudentFeedbacks(studentId);
            break;
        case 0:
            printf("感谢使用本系统...\n");
            break;
        default:
            printf("无效选择，请重新输入！\n");
        }
    } while (choice != 0);

    saveAllData(); // 保存所有数据
}

// 学生提交反馈
void studentFeedback(int studentId) {
    if (feedbackCount >= MAX_FEEDBACKS) {
        printf("反馈列表已满，无法提交反馈！\n");
        return;
    }

    printf("\n===== 提交反馈 =====\n");

    // 输入商家信息 - 处理无效输入
    int merchantId;
    do {
        printf("请输入商家编号: ");
        while (scanf("%d", &merchantId) != 1) {
            printf("输入无效，请重新输入: ");
            while (getchar() != '\n'); // 清空输入缓冲区
        }
        while (getchar() != '\n'); // 清除剩余字符
    } while (merchantId <= 0);

    // 输入反馈问题
    printf("请输入反馈问题内容: ");
    if (fgets(feedbacks[feedbackCount].problem, 150, stdin) == NULL) {
        printf("输入错误\n");
        return;
    }
    feedbacks[feedbackCount].problem[strcspn(feedbacks[feedbackCount].problem, "\n")] = 0; // 去除换行符

    // 填充反馈信息
    feedbacks[feedbackCount].id = feedbackCount + 1;
    feedbacks[feedbackCount].studentId = studentId;
    feedbacks[feedbackCount].merchantId = merchantId;
    strcpy(feedbacks[feedbackCount].time, getCurrentTime());
    strcpy(feedbacks[feedbackCount].reply, "未回复"); // 初始状态

    printf("反馈提交成功，反馈编号: %d\n", feedbacks[feedbackCount].id);
    feedbackCount++;

    saveAllData();
}

// 保存所有数据到文本文件
void saveAllData() {
    FILE* file;

    // 打开反馈数据的文本文件
    file = fopen("feedbacks.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < feedbackCount; i++) {
            if (fprintf(file, "%d,%d,%d,%s,%s,%s\n",
                feedbacks[i].id,
                feedbacks[i].studentId,
                feedbacks[i].merchantId,
                feedbacks[i].problem,
                feedbacks[i].reply,
                feedbacks[i].time) < 0) {
                printf("写入反馈数据失败\n");
                break;
            }
        }
        fclose(file);
    }
    else {
        printf("无法打开反馈文件\n");
    }
}

// 从文本文件加载所有反馈数据
void loadAllData() {
    FILE* file;
    char line[512]; // 足够长的缓冲区

    // 重置反馈计数
    feedbackCount = 0;

    // 从文本文件读取反馈数据
    file = fopen("feedbacks.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file) != NULL && feedbackCount < MAX_FEEDBACKS) {
            // 格式: id,studentId,merchantId,problem,reply,time
            if (sscanf(line, "%d,%d,%d,%[^,],%[^,],%[^\n]",
                &feedbacks[feedbackCount].id,
                &feedbacks[feedbackCount].studentId,
                &feedbacks[feedbackCount].merchantId,
                feedbacks[feedbackCount].problem,
                feedbacks[feedbackCount].reply,
                feedbacks[feedbackCount].time) != 6) {
                continue; // 跳过格式错误的行
            }
            feedbackCount++;
        }
        fclose(file);
    }
}

// 显示学生的反馈记录
void displayStudentFeedbacks(int studentId) {
    printf("\n===== 我的反馈记录 =====\n");
    int found = 0;

    for (int i = 0; i < feedbackCount; i++) {
        if (feedbacks[i].studentId == studentId) {
            printf("\n反馈编号: %d\n", feedbacks[i].id);
            printf("商家编号: %d\n", feedbacks[i].merchantId);
            printf("反馈问题: %s\n", feedbacks[i].problem);
            printf("回复内容: %s\n", feedbacks[i].reply);
            printf("提交时间: %s\n", feedbacks[i].time);
            printf("----------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("暂无反馈记录！\n");
    }
}
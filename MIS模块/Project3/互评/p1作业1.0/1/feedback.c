#include "main.h"
#include "stu.h"
#include "food.h"
#include "dish.h"

Feedback feedbacks[MAX_FEEDBACKS];
int feedbackCount = 0;

// ��ȡ��ǰʱ�䣨����ӷ���ֵ��飩
char* getCurrentTime() {
    static char timeStr[20] = ""; // ȷ����Ĭ��ֵ
    time_t now;
    struct tm* timeinfo;

    time(&now); // ����ԭ��������鷵��ֵ
    timeinfo = localtime(&now); // ����ԭ��
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", timeinfo); // ����ԭ��

    return timeStr;
}

// �̼Ҳ˵�������������飩
void merchantMenu(int merchantId) {
    loadAllData(); // ����ԭ��
    int n;
    do {
        printf("\n===== �̼Ҳ˵� =====\n");
        printf("1. ��ƷԤ��\n");
        printf("2. ��Ʒ�޸�\n");
        printf("3. �鿴����\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");

        if (scanf("%d", &n) != 1) { // �����������
            n = -1; // ����ԭ�д���������
        }

        while (getchar() != '\n'); // ����ԭ��

        switch (n) { // ԭ���߼���ȫ����
        case 1: foodv(merchantId); break;
        case 2: DishModify(merchantId); break;
        case 3: marchantFeedback(merchantId); break;
        case 0: printf("�˳��̼Ҳ˵�...\n"); break;
        default: printf("��Чѡ�����������룡\n");
        }
    } while (n != 0);
    saveAllData(); // ����ԭ��
}

// �鿴�̼ҷ���������������飩
void marchantFeedback(int merchantId) {
    printf("\n===== �̼ҷ�����Ϣ =====\n");
    printf("�̼ұ��: %d\n", merchantId);
    printf("========================\n");

    int found = 0;
    for (int i = 0; i < feedbackCount; i++) {
        if (feedbacks[i].merchantId == merchantId) {
            printf("\n�������: %d\n", feedbacks[i].id);
            printf("�ύʱ��: %s\n", feedbacks[i].time);
            printf("��������: %s\n", feedbacks[i].problem);
            printf("�ظ�����: %s\n", feedbacks[i].reply);
            printf("------------------------\n");
            found = 1;

            int choice;
            do {
                printf("\n===== �̼һظ��˵� =====\n");
                printf("1. �ظ�\n");
                printf("0. �˳�\n");
                printf("��ѡ��: ");

                if (scanf("%d", &choice) != 1) { // �����������
                    choice = -1; // ����ԭ�д�����
                }

                while (getchar() != '\n'); // ����ԭ��

                switch (choice) { // ԭ���߼���ȫ����
                case 1: replyToFeedback(); break;
                case 0: printf("�˳��̼һظ��˵�...\n"); break;
                default: printf("��Чѡ�����������룡\n");
                }
            } while (choice != 0);
        }
    }
    if (!found) {
        printf("���޷�����¼��\n"); // ����ԭ��
    }
}

// �ظ�����������ӱ�Ҫ��飩
void replyToFeedback() {
    int feedbackId;
    printf("\n������Ҫ�ظ��ķ������ (0����): ");

    if (scanf("%d", &feedbackId) != 1) { // �����������
        feedbackId = 0; // ����ԭ������
    }
    getchar(); // ����ԭ��

    if (feedbackId == 0) return;

    Feedback* target = NULL;
    for (int i = 0; i < feedbackCount; i++) {
        if (feedbacks[i].id == feedbackId) {
            target = &feedbacks[i];
            break;
        }
    }

    if (!target) {
        printf("δ�ҵ��÷�����\n"); // ����ԭ��
        return;
    }

    printf("\n��ǰ������Ϣ:\n");
    printf("��������: %s\n", target->problem);
    printf("��ǰ�ظ�: %s\n", target->reply);

    printf("\n������ظ�����: ");
    char newReply[150];
    if (fgets(newReply, sizeof(newReply), stdin) == NULL) { // ����Ӽ��
        newReply[0] = '\0'; // ����ԭ������
    }
    newReply[strcspn(newReply, "\n")] = '\0'; // ����ԭ��

    if (strlen(newReply) > 0) { // ԭ���߼���ȫ����
        strncpy(target->reply, newReply, sizeof(target->reply));
        target->reply[sizeof(target->reply) - 1] = '\0'; // ȷ����ֹ��

        // ����ԭ��ʱ������߼�
        char* timeStr = getCurrentTime();
        strncpy(target->time, timeStr, sizeof(target->time));
        target->time[sizeof(target->time) - 1] = '\0';

        saveAllData(); // ����ԭ��
        printf("�ظ��Ѹ��£�\n");
    }
    else {
        printf("�ظ����ݲ���Ϊ�գ�\n"); // ����ԭ��
    }
}
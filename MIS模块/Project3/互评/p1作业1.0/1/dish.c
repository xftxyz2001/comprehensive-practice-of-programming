#include "main.h"
#include "dish.h"
#include <errno.h>  // ���ڴ�����

// �����̼�ר���ļ���
char* getMerchantFileName(int merchantId) {
    static char fileName[50];
    if (snprintf(fileName, sizeof(fileName), "merchant_%d_dishes.txt", merchantId) < 0) {
        perror("�����ļ���ʧ��");
        fileName[0] = '\0'; // ���ؿ��ַ���
    }
    return fileName;
}

// ��Ʒ�޸ĺ����������̼�ID��Ϊ������
void DishModify(int merchantId) {
    FILE* fp = NULL, * temp = NULL;
    char line[256];
    char id[10], inputId[10], name[30], newName[30];
    float price, newPrice;
    int choice, found = 0;
    char* fileName = getMerchantFileName(merchantId);

    if (fileName[0] == '\0') {
        return; // �ļ�������ʧ��
    }

    printf("\n--- ��Ʒ��Ϣ���� ---\n");
    printf("1. ��Ӳ�Ʒ\n");
    printf("2. ɾ����Ʒ\n");
    printf("3. �޸Ĳ�Ʒ\n");
    printf("������������: ");
    if (scanf("%d", &choice) != 1) {
        printf("������Ч\n");
        while (getchar() != '\n'); // ������뻺����
        return;
    }
    getchar();  // ������뻺����

    switch (choice) {
    case 1:  // ��Ӳ�Ʒ
        printf("�������Ʒ���: ");
        if (scanf("%9s", id) != 1) {
            printf("��Ʒ���������Ч\n");
            break;
        }
        printf("�������Ʒ����: ");
        if (scanf("%29s", name) != 1) {
            printf("��Ʒ����������Ч\n");
            break;
        }
        printf("�������Ʒ�۸�: ");
        if (scanf("%f", &price) != 1) {
            printf("�۸�������Ч\n");
            break;
        }

        fp = fopen(fileName, "a");
        if (fp == NULL) {
            perror("�޷����ļ�");
            break;
        }
        if (fprintf(fp, "%s %s %.2f %d\n", id, name, price, merchantId) < 0) {
            perror("д���ļ�ʧ��");
        }
        else {
            printf("��ӳɹ�\n");
        }
        if (fclose(fp) != 0) {
            perror("�ر��ļ�ʧ��");
        }
        break;

    case 2:  // ɾ����Ʒ
        printf("������Ҫɾ���Ĳ�Ʒ���: ");
        if (scanf("%9s", inputId) != 1) {
            printf("��Ʒ���������Ч\n");
            break;
        }

        fp = fopen(fileName, "r");
        if (fp == NULL) {
            perror("�޷���Դ�ļ�");
            break;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            perror("�޷�������ʱ�ļ�");
            fclose(fp);
            break;
        }

        found = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (sscanf(line, "%9s %29s %f %d", id, name, &price, &merchantId) != 4) {
                continue; // ������ʽ�������
            }
            if (strcmp(inputId, id) == 0) {
                found = 1;
                continue;  // ������ǰ�У���ɾ��
            }
            if (fputs(line, temp) == EOF) {
                perror("д����ʱ�ļ�ʧ��");
                break;
            }
        }

        if (fclose(fp) != 0) {
            perror("�ر�Դ�ļ�ʧ��");
        }
        if (fclose(temp) != 0) {
            perror("�ر���ʱ�ļ�ʧ��");
        }

        if (found) {
            if (remove(fileName) != 0) {
                perror("ɾ��ԭ�ļ�ʧ��");
            }
            else if (rename("temp.txt", fileName) != 0) {
                perror("�������ļ�ʧ��");
            }
            else {
                printf("ɾ���ɹ�\n");
            }
        }
        else {
            if (remove("temp.txt") != 0) {
                perror("ɾ����ʱ�ļ�ʧ��");
            }
            printf("δ�ҵ��ò�Ʒ\n");
        }
        break;

    case 3:  // �޸Ĳ�Ʒ
        printf("������Ҫ�޸ĵĲ�Ʒ���: ");
        if (scanf("%9s", inputId) != 1) {
            printf("��Ʒ���������Ч\n");
            break;
        }

        fp = fopen(fileName, "r");
        if (fp == NULL) {
            perror("�޷���Դ�ļ�");
            break;
        }
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            perror("�޷�������ʱ�ļ�");
            fclose(fp);
            break;
        }

        found = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (sscanf(line, "%9s %29s %f %d", id, name, &price, &merchantId) != 4) {
                if (fputs(line, temp) == EOF) {
                    perror("д����ʱ�ļ�ʧ��");
                }
                continue;
            }
            if (strcmp(inputId, id) == 0) {
                found = 1;
                printf("��ǰ��Ʒ: %s %s %.2f\n", id, name, price);
                printf("������������: ");
                if (scanf("%29s", newName) != 1) {
                    printf("����������Ч\n");
                    fputs(line, temp); // ����ԭ����
                    continue;
                }
                printf("�������¼۸�: ");
                if (scanf("%f", &newPrice) != 1) {
                    printf("�۸�������Ч\n");
                    fputs(line, temp); // ����ԭ����
                    continue;
                }
                if (fprintf(temp, "%s %s %.2f %d\n", id, newName, newPrice, merchantId) < 0) {
                    perror("д����ʱ�ļ�ʧ��");
                }
            }
            else {
                if (fputs(line, temp) == EOF) {
                    perror("д����ʱ�ļ�ʧ��");
                }
            }
        }

        if (fclose(fp) != 0) {
            perror("�ر�Դ�ļ�ʧ��");
        }
        if (fclose(temp) != 0) {
            perror("�ر���ʱ�ļ�ʧ��");
        }

        if (found) {
            if (remove(fileName) != 0) {
                perror("ɾ��ԭ�ļ�ʧ��");
            }
            else if (rename("temp.txt", fileName) != 0) {
                perror("�������ļ�ʧ��");
            }
            else {
                printf("�޸ĳɹ�\n");
            }
        }
        else {
            if (remove("temp.txt") != 0) {
                perror("ɾ����ʱ�ļ�ʧ��");
            }
            printf("δ�ҵ��ò�Ʒ\n");
        }
        break;

    default:
        printf("��Чѡ��\n");
    }
}
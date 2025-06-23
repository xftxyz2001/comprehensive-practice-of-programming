#ifndef FOOD_H
#define FOOD_H

#define MAX_FOODS 200
#define NAME_LEN 30
#define STORE_LEN 11
#define COMMENT_LEN 128
#define ID_LEN 10

typedef struct {
    char id[ID_LEN];          // ��ƷID
    char store[STORE_LEN];    // �̼����ƣ������ֶΣ�
    char name[NAME_LEN];      // ��Ʒ����
    float price;              // �۸�
    char comment[COMMENT_LEN];// ���ۣ������ֶΣ�
} Food;

// ����ԭ�к�����������
int foodv(int studentId);

#endif
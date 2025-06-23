#ifndef FOOD_H
#define FOOD_H

#define MAX_FOODS 200
#define NAME_LEN 30
#define STORE_LEN 11
#define COMMENT_LEN 128
#define ID_LEN 10

typedef struct {
    char id[ID_LEN];          // 菜品ID
    char store[STORE_LEN];    // 商家名称（保留字段）
    char name[NAME_LEN];      // 菜品名称
    float price;              // 价格
    char comment[COMMENT_LEN];// 评论（保留字段）
} Food;

// 保持原有函数声明不变
int foodv(int studentId);

#endif
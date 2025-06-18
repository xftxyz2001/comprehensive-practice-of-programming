#ifndef ENTITY_H
#define ENTITY_H

typedef struct
{
    int userID;
    char username[20];
    char password[20];
    int isAdmin; // 0:普通用户 1:管理员
} User;

typedef struct
{
    int productID;
    int ownerID; // 对应用户ID
    char name[50];
    char description[200];
    float price;
    int createTime;
    int isSold; // 0:未售 1:已售
} Product;

typedef struct
{
    int messageID;
    int userID;
    int productID;
    char message[200];
    int createTime;
} Message;

typedef struct
{
    int orderID;
    int userID;
    int productID;
    float price;
    int createTime;
} Order;

#endif // ENTITY_H

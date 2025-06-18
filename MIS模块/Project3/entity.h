#ifndef ENTITY_H
#define ENTITY_H

typedef struct
{
    int userID;
    char username[20];
    char password[20];
    int isAdmin; // 0:��ͨ�û� 1:����Ա
} User;

typedef struct
{
    int productID;
    int ownerID; // ��Ӧ�û�ID
    char name[50];
    char description[200];
    double price;
    int createTime;
    int isSold; // 0:δ�� 1:����
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
    int ownerID;           // ��Ʒ��Ϣ
    char name[50];         // ��Ʒ��Ϣ
    char description[200]; // ��Ʒ��Ϣ
    double price;          // ��Ʒ��Ϣ
    int createTime;
} Order;

#endif // ENTITY_H

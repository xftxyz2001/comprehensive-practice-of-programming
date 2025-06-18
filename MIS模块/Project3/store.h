#ifndef STORE_H
#define STORE_H

#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    User *data;
    int size;
    int capacity;
} UserList;

int addUser(User u);
int deleteUserByID(int userID);
UserList *getUserList();
User *findUserByID(int userID);
User *findUserByUsername(char *username);

typedef struct
{
    Product *data;
    int size;
    int capacity;
} ProductList;

int addProduct(Product p);
int deleteProductByID(int productID);
ProductList *getProductList();
ProductList *getOnSaleProductList();
ProductList *getMyPublishProductList(int userID);
Product *findProductByID(int productID);

typedef struct
{
    Message *data;
    int size;
    int capacity;
} MessageList;

int addMessage(Message m);
int deleteMessageByID(int messageID);
MessageList *getMessageList();

typedef struct
{
    Order *data;
    int size;
    int capacity;
} OrderList;

int addOrder(Order o);
int deleteOrderByID(int orderID);
OrderList *getOrderList();
OrderList *getMyPurchaseList(int userID);

int initStore();
int destroyStore();

#endif // STORE_H

// order.h
#ifndef ORDER_H
#define ORDER_H

#include <ctime>
using namespace std;

struct Product; // Ç°ÏòÉùÃ÷

#define MAX_ORDERS 100

struct Order {
    int orderID;
    int buyerID;
    int productID;
    float price;
    time_t createTime;
};

struct OrderList {
    Order* data;
    int count;
};

extern Order orders[MAX_ORDERS];
extern int orderCount;

int loadOrders();
int saveOrders();
int addOrder(const Order& order);
void showMyOrders();

#endif

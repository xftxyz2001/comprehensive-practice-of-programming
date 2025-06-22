// order.cpp
#include "order.h"
#include "user.h"
#include "product.h"
#include "utils.h"

Order orders[MAX_ORDERS];
int orderCount = 0;

int loadOrders() {
    FILE* file = fopen("orders.bin", "rb");
    if (!file) return 0;
    orderCount = fread(orders, sizeof(Order), MAX_ORDERS, file);
    fclose(file);
    return 1;
}

int saveOrders() {
    FILE* file = fopen("orders.bin", "wb");
    if (!file) return 0;
    fwrite(orders, sizeof(Order), orderCount, file);
    fclose(file);
    return 1;
}

int addOrder(const Order& order) {
    if (orderCount >= MAX_ORDERS) return 0;
    orders[orderCount++] = order;
    return saveOrders();
}

void showMyOrders() {
    if (!currentUser) {
        cout << "请先登录！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("我的购买");
    
    int count = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].buyerID == currentUser->userID) {
            cout << "[" << ++count << "] ";
            
            Product* product = findProductByID(orders[i].productID);
            cout << "订单ID: " << orders[i].orderID << endl;
            cout << "商品: " << (product ? product->name : "已删除") << endl;
            cout << "价格: " << orders[i].price << "元" << endl;
            cout << "购买时间: " << ctime(&orders[i].createTime);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "您还没有购买任何商品！" << endl;
    }
    
    pressAnyKeyToContinue();
}

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
        cout << "���ȵ�¼��" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("�ҵĹ���");
    
    int count = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].buyerID == currentUser->userID) {
            cout << "[" << ++count << "] ";
            
            Product* product = findProductByID(orders[i].productID);
            cout << "����ID: " << orders[i].orderID << endl;
            cout << "��Ʒ: " << (product ? product->name : "��ɾ��") << endl;
            cout << "�۸�: " << orders[i].price << "Ԫ" << endl;
            cout << "����ʱ��: " << ctime(&orders[i].createTime);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "����û�й����κ���Ʒ��" << endl;
    }
    
    pressAnyKeyToContinue();
}

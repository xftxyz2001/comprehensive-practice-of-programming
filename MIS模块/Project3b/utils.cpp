#include "utils.h"
#include "user.h"  // 确保包含 user.h
#include "product.h"

void printHeader(const string& title) {
    system("cls");
    cout << "==== " << title << " ====" << endl << endl;
}

void pressAnyKeyToContinue() {
    cout << "按任意键继续...";
    getch();
    cout << endl;
}

void printProduct(const Product* product) {
    User* seller = getUserByID(product->sellerID);
    
    cout << "商品ID: " << product->productID << endl;
    cout << "名称: " << product->name << endl;
    cout << "价格: " << product->price << "元" << endl;
    cout << "描述: " << product->description << endl;
    cout << "卖家: " << (seller ? seller->username : "未知") << endl;
    cout << "状态: " << (product->status ? "已售出" : "在售") << endl;
    cout << "发布时间: " << ctime(&product->createTime);
}

User* getUserByID(int userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userID == userID) {
            return &users[i];
        }
    }
    return nullptr;
}

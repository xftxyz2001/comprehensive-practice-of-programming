// main.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <conio.h>
using namespace std;

#include "user.h"
#include "product.h"
#include "order.h"
#include "utils.h"

void mainMenu();
void userMenu();

int main() {
    loadUsers();
    loadProducts();
    loadOrders();
    
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    while (1) {
        system("cls");
        printHeader("XF学校二手市场交易系统");
        cout << "1. 注册" << endl;
        cout << "2. 登录" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: registerUser(); break;
            case 2: login(); break;
            case 0: cout << "感谢使用，再见！" << endl; return;
            default: cout << "无效选择，请重新输入！" << endl; pressAnyKeyToContinue();
        }
    }
}

// main.cpp
void userMenu() {
    if (!currentUser) return;
    
    int choice;
    while (1) {
        system("cls");
        printHeader("用户中心 - " + string(currentUser->username));
        cout << "1. 浏览商品" << endl;
        cout << "2. 发布商品" << endl;
        cout << "3. 我的发布" << endl;
        cout << "4. 我的购买" << endl;
        cout << "0. 退出登录" << endl;
        cout << "请选择: ";
        
        // 确保输入有效
        if (!(cin >> choice)) {
            cin.clear();  // 清除错误标志
            cin.ignore(10000, '\n');  // 忽略缓冲区中的剩余字符
            cout << "无效输入，请输入数字！" << endl;
            pressAnyKeyToContinue();
            continue;
        }
        cin.ignore();  // 清除换行符
        
        switch (choice) {
            case 1: showProductList(); break;
            case 2: publishProduct(); break;
            case 3: showMyProducts(); break;
            case 4: showMyOrders(); break;
            case 0: 
                cout << "已退出登录！" << endl;
                currentUser = NULL;
                pressAnyKeyToContinue();
                return;  // 只有选择0时才退出函数
            default: 
                cout << "无效选择，请重新输入！" << endl;
                pressAnyKeyToContinue();
        }
        
        // 不需要在这里调用 pressAnyKeyToContinue()，因为每个功能函数内部已经调用过
    }
}

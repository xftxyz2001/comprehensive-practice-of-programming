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
        printHeader("XFѧУ�����г�����ϵͳ");
        cout << "1. ע��" << endl;
        cout << "2. ��¼" << endl;
        cout << "0. �˳�" << endl;
        cout << "��ѡ��: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: registerUser(); break;
            case 2: login(); break;
            case 0: cout << "��лʹ�ã��ټ���" << endl; return;
            default: cout << "��Чѡ�����������룡" << endl; pressAnyKeyToContinue();
        }
    }
}

// main.cpp
void userMenu() {
    if (!currentUser) return;
    
    int choice;
    while (1) {
        system("cls");
        printHeader("�û����� - " + string(currentUser->username));
        cout << "1. �����Ʒ" << endl;
        cout << "2. ������Ʒ" << endl;
        cout << "3. �ҵķ���" << endl;
        cout << "4. �ҵĹ���" << endl;
        cout << "0. �˳���¼" << endl;
        cout << "��ѡ��: ";
        
        // ȷ��������Ч
        if (!(cin >> choice)) {
            cin.clear();  // ��������־
            cin.ignore(10000, '\n');  // ���Ի������е�ʣ���ַ�
            cout << "��Ч���룬���������֣�" << endl;
            pressAnyKeyToContinue();
            continue;
        }
        cin.ignore();  // ������з�
        
        switch (choice) {
            case 1: showProductList(); break;
            case 2: publishProduct(); break;
            case 3: showMyProducts(); break;
            case 4: showMyOrders(); break;
            case 0: 
                cout << "���˳���¼��" << endl;
                currentUser = NULL;
                pressAnyKeyToContinue();
                return;  // ֻ��ѡ��0ʱ���˳�����
            default: 
                cout << "��Чѡ�����������룡" << endl;
                pressAnyKeyToContinue();
        }
        
        // ����Ҫ��������� pressAnyKeyToContinue()����Ϊÿ�����ܺ����ڲ��Ѿ����ù�
    }
}

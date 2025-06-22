#include "utils.h"
#include "user.h"  // ȷ������ user.h
#include "product.h"

void printHeader(const string& title) {
    system("cls");
    cout << "==== " << title << " ====" << endl << endl;
}

void pressAnyKeyToContinue() {
    cout << "�����������...";
    getch();
    cout << endl;
}

void printProduct(const Product* product) {
    User* seller = getUserByID(product->sellerID);
    
    cout << "��ƷID: " << product->productID << endl;
    cout << "����: " << product->name << endl;
    cout << "�۸�: " << product->price << "Ԫ" << endl;
    cout << "����: " << product->description << endl;
    cout << "����: " << (seller ? seller->username : "δ֪") << endl;
    cout << "״̬: " << (product->status ? "���۳�" : "����") << endl;
    cout << "����ʱ��: " << ctime(&product->createTime);
}

User* getUserByID(int userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userID == userID) {
            return &users[i];
        }
    }
    return nullptr;
}

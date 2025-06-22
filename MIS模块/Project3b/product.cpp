// product.cpp
#include "product.h"
#include "user.h"
#include "order.h"
#include "utils.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

int loadProducts() {
    FILE* file = fopen("products.bin", "rb");
    if (!file) return 0;
    productCount = fread(products, sizeof(Product), MAX_PRODUCTS, file);
    fclose(file);
    return 1;
}

// product.cpp
int saveProducts() {
    FILE* file = fopen("products.bin", "wb");
    if (file == NULL) {
        cout << "�����޷�������Ʒ���ݣ�" << endl;
        return 0;
    }
    
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
    return 1;
}
Product* findProductByID(int productID) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == productID) {
            return &products[i];
        }
    }
    return NULL;
}

void showProductList() {
    printHeader("��Ʒ�б�");
    
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].status == 0) { // ����
            cout << "[" << ++count << "] ";
            printProduct(&products[i]);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "����������Ʒ��" << endl;
    } else {
        cout << "������Ʒ��Ź��򣬻�0����: ";
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice > 0 && choice <= count) {
            int index = 0;
            for (int i = 0; i < productCount && index < choice; i++) {
                if (products[i].status == 0) index++;
                if (index == choice) {
                    buyProduct(products[i].productID);
                    break;
                }
            }
        }
    }
    
    pressAnyKeyToContinue();
}

// product.cpp
void publishProduct() {
    if (!currentUser) {
        cout << "���ȵ�¼��" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("������Ʒ");
    
    Product newProduct;
    
    cout << "��Ʒ����: ";
    cin.getline(newProduct.name, 50);
    
    cout << "��Ʒ�۸�: ";
    cin >> newProduct.price;
    cin.ignore();  // ������뻺�����Ļ��з�
    
    cout << "��Ʒ����: ";
    cin.getline(newProduct.description, 200);
    
    // �޸���ȷ�� nextProductID �� 1 ��ʼ����ÿ�ε���
    static int nextProductID = 1;
    newProduct.productID = nextProductID++;
    
    newProduct.sellerID = currentUser->userID;
    newProduct.status = 0; // ����
    newProduct.createTime = time(nullptr);
    
    products[productCount++] = newProduct;
    saveProducts();
    
    cout << "��Ʒ�����ɹ���" << endl;
    pressAnyKeyToContinue();
}

void showMyProducts() {
    if (!currentUser) {
        cout << "���ȵ�¼��" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("�ҵķ���");
    
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].sellerID == currentUser->userID) {
            cout << "[" << ++count << "] ";
            printProduct(&products[i]);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "����û�з����κ���Ʒ��" << endl;
    }
    
    pressAnyKeyToContinue();
}

void buyProduct(int productID) {
    if (!currentUser) {
        cout << "���ȵ�¼��" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    Product* product = findProductByID(productID);
    if (!product) {
        cout << "��Ʒ�����ڣ�" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    if (product->status == 1) {
        cout << "����Ʒ���۳���" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    if (product->sellerID == currentUser->userID) {
        cout << "�����ܹ����Լ���������Ʒ��" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("ȷ�Ϲ���");
    printProduct(product);
    
    cout << "ȷ�Ϲ������Ʒ��(Y/N): ";
    char confirm;
    cin >> confirm;
    cin.ignore();
    
    if (confirm == 'Y' || confirm == 'y') {
        // ��������
        Order order;
        static int nextOrderID = 1;
        order.orderID = nextOrderID++;
        order.buyerID = currentUser->userID;
        order.productID = productID;
        order.price = product->price;
        order.createTime = time(NULL);
        
        addOrder(order);
        
        // ������Ʒ״̬
        product->status = 1;
        saveProducts();
        
        cout << "����ɹ���" << endl;
    }
    
    pressAnyKeyToContinue();
}

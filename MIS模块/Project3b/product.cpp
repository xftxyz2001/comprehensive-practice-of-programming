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
        cout << "错误：无法保存商品数据！" << endl;
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
    printHeader("商品列表");
    
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].status == 0) { // 在售
            cout << "[" << ++count << "] ";
            printProduct(&products[i]);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "暂无在售商品！" << endl;
    } else {
        cout << "输入商品编号购买，或按0返回: ";
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
        cout << "请先登录！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("发布商品");
    
    Product newProduct;
    
    cout << "商品名称: ";
    cin.getline(newProduct.name, 50);
    
    cout << "商品价格: ";
    cin >> newProduct.price;
    cin.ignore();  // 清除输入缓冲区的换行符
    
    cout << "商品描述: ";
    cin.getline(newProduct.description, 200);
    
    // 修复：确保 nextProductID 从 1 开始，且每次递增
    static int nextProductID = 1;
    newProduct.productID = nextProductID++;
    
    newProduct.sellerID = currentUser->userID;
    newProduct.status = 0; // 在售
    newProduct.createTime = time(nullptr);
    
    products[productCount++] = newProduct;
    saveProducts();
    
    cout << "商品发布成功！" << endl;
    pressAnyKeyToContinue();
}

void showMyProducts() {
    if (!currentUser) {
        cout << "请先登录！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("我的发布");
    
    int count = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].sellerID == currentUser->userID) {
            cout << "[" << ++count << "] ";
            printProduct(&products[i]);
            cout << endl;
        }
    }
    
    if (count == 0) {
        cout << "您还没有发布任何商品！" << endl;
    }
    
    pressAnyKeyToContinue();
}

void buyProduct(int productID) {
    if (!currentUser) {
        cout << "请先登录！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    Product* product = findProductByID(productID);
    if (!product) {
        cout << "商品不存在！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    if (product->status == 1) {
        cout << "该商品已售出！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    if (product->sellerID == currentUser->userID) {
        cout << "您不能购买自己发布的商品！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    printHeader("确认购买");
    printProduct(product);
    
    cout << "确认购买此商品吗？(Y/N): ";
    char confirm;
    cin >> confirm;
    cin.ignore();
    
    if (confirm == 'Y' || confirm == 'y') {
        // 创建订单
        Order order;
        static int nextOrderID = 1;
        order.orderID = nextOrderID++;
        order.buyerID = currentUser->userID;
        order.productID = productID;
        order.price = product->price;
        order.createTime = time(NULL);
        
        addOrder(order);
        
        // 更新商品状态
        product->status = 1;
        saveProducts();
        
        cout << "购买成功！" << endl;
    }
    
    pressAnyKeyToContinue();
}

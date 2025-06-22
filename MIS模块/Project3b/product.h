// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <ctime>
using namespace std;

struct User; // 前向声明

#define MAX_PRODUCTS 100

struct Product {
    int productID;
    char name[50];
    float price;
    char description[200];
    int sellerID;
    int status; // 0-在售，1-已售出
    time_t createTime;
};

struct ProductList {
    Product* data;
    int count;
};

extern Product products[MAX_PRODUCTS];
extern int productCount;

int loadProducts();
int saveProducts();
Product* findProductByID(int productID);
void showProductList();
void publishProduct();
void showMyProducts();
void buyProduct(int productID);

#endif

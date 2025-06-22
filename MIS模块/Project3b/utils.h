#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

// 为不支持 C++11 的编译器定义 nullptr
#ifndef nullptr
#define nullptr 0
#endif
struct User;  
struct Product;

void printHeader(const string& title);
void pressAnyKeyToContinue();
void printProduct(const Product* product);
User* getUserByID(int userID);  // 声明函数

#endif

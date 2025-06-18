#ifndef STORE_H
#define STORE_H

#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addUser(User u);
int deleteUserByID(int userID);
User *findUserByUsername(char *username);

int addProduct(Product p);
int deleteProductByID(int productID);

int addMessage(Message m);

int addOrder(Order o);

int initStore();
int destroyStore();

#endif // STORE_H

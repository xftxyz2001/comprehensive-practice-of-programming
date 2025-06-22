// user.h
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

#define MAX_USERS 100

struct User {
    int userID;
    char username[50];
    char password[50];
};

extern User users[MAX_USERS];
extern int userCount;
extern User* currentUser;

int loadUsers();
int saveUsers();
User* findUserByUsername(const char* username);
void registerUser();
void login();
// ÉùÃ÷ userMenu()
void userMenu();
#endif

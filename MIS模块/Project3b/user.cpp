// user.cpp
#include "user.h"
#include "utils.h"
#include <cstring> 
User users[MAX_USERS];
int userCount = 0;
User* currentUser = NULL;

int loadUsers() {
    FILE* file = fopen("users.bin", "rb");
    if (!file) return 0;
    userCount = fread(users, sizeof(User), MAX_USERS, file);
    fclose(file);
    return 1;
}

int saveUsers() {
    FILE* file = fopen("users.bin", "wb");
    if (!file) return 0;
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    return 1;
}

User* findUserByUsername(const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

void registerUser() {
    printHeader("用户注册");
    
    User newUser;
    char username[50];
    
    while (1) {
        cout << "请输入用户名: ";
        cin.getline(username, 50);
        
        if (findUserByUsername(username)) {
            cout << "用户名已存在，请重新输入！" << endl;
        } else {
            strcpy(newUser.username, username);
            break;
        }
    }
    
    cout << "请输入密码: ";
    cin.getline(newUser.password, 50);
    
    static int nextUserID = 1;
    newUser.userID = nextUserID++;
    
    users[userCount++] = newUser;
    saveUsers();
    
    cout << "注册成功！" << endl;
    pressAnyKeyToContinue();
}

void login() {
    printHeader("用户登录");
    
    char username[50], password[50];
    
    cout << "请输入用户名: ";
    cin.getline(username, 50);
    
    User* user = findUserByUsername(username);
    if (!user) {
        cout << "用户名不存在！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    cout << "请输入密码: ";
    cin.getline(password, 50);
    
    if (strcmp(user->password, password) != 0) {
        cout << "密码错误！" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    currentUser = user;
    cout << "登录成功，欢迎 " << user->username << "！" << endl;
    pressAnyKeyToContinue();
    userMenu();
}

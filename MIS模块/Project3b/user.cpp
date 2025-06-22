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
    printHeader("�û�ע��");
    
    User newUser;
    char username[50];
    
    while (1) {
        cout << "�������û���: ";
        cin.getline(username, 50);
        
        if (findUserByUsername(username)) {
            cout << "�û����Ѵ��ڣ����������룡" << endl;
        } else {
            strcpy(newUser.username, username);
            break;
        }
    }
    
    cout << "����������: ";
    cin.getline(newUser.password, 50);
    
    static int nextUserID = 1;
    newUser.userID = nextUserID++;
    
    users[userCount++] = newUser;
    saveUsers();
    
    cout << "ע��ɹ���" << endl;
    pressAnyKeyToContinue();
}

void login() {
    printHeader("�û���¼");
    
    char username[50], password[50];
    
    cout << "�������û���: ";
    cin.getline(username, 50);
    
    User* user = findUserByUsername(username);
    if (!user) {
        cout << "�û��������ڣ�" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    cout << "����������: ";
    cin.getline(password, 50);
    
    if (strcmp(user->password, password) != 0) {
        cout << "�������" << endl;
        pressAnyKeyToContinue();
        return;
    }
    
    currentUser = user;
    cout << "��¼�ɹ�����ӭ " << user->username << "��" << endl;
    pressAnyKeyToContinue();
    userMenu();
}

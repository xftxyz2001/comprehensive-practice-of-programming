#include "menu.h"

User *currentUser;

void productList()
{
}

void publishProduct()
{
}

void myPublish()
{
}

void myPurchase()
{
}

void productManagement()
{
}

void userManagement()
{
}

void messageManagement()
{
}

void orderManagement()
{
}

void userMenu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("\nXF二手市场系统 -- 用户菜单\n");
        printf("1. 商品列表\n");
        printf("2. 发布商品\n");
        printf("3. 我的发布\n");
        printf("4. 我的购买\n");
        printf("0. 退出登录\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            productList();
            break;
        case 2:
            publishProduct();
            break;
        case 3:
            myPublish();
            break;
        case 4:
            myPurchase();
            break;
        case 0:
            currentUser = NULL;
            break;
        default:
            printf("无效选项。\n");
            _sleep(500);
        }
    }
}

void adminMenu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("\nXF二手市场系统 -- 管理员菜单\n");
        printf("1. 商品管理\n");
        printf("2. 用户管理\n");
        printf("3. 评论管理\n");
        printf("4. 订单管理\n");
        printf("0. 退出登录\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            productManagement();
            break;
        case 2:
            userManagement();
            break;
        case 3:
            messageManagement();
            break;
        case 4:
            orderManagement();
            break;
        case 0:
            currentUser = NULL;
            break;
        default:
            printf("无效选项。\n");
            _sleep(500);
        }
    }
}

void registerUser()
{
    system("cls");
    printf("XF二手市场系统 -- 注册\n");

    User newUser;
    printf("输入用户名: ");
    for (;;)
    {
        scanf("%s", newUser.username);
        User *existUser = findUserByUsername(newUser.username);
        if (existUser == NULL)
        {
            break;
        }
        printf("用户名已存在，请重新输入: ");
    }
    printf("输入密码: ");
    scanf("%s", newUser.password);
    if (addUser(newUser))
    {
        printf("注册成功！\n");
    }
    else
    {
        printf("注册失败！\n");
    }
    _sleep(500);
}

void inputPassword(char *password)
{
    char ch;
    int index = 0;

    while (1)
    {
        ch = _getch(); // 读取一个字符但不显示
        if (ch == '\r')
        { // 回车结束输入
            break;
        }
        else if (ch == '\b')
        { // 退格键
            if (index > 0)
            {
                index--;
                printf("\b \b"); // 删除显示的 *
            }
        }
        else if (index < 19 && ch >= 32 && ch <= 126)
        { // 限制密码长度
            password[index++] = ch;
            printf("*");
        }
    }

    password[index] = '\0'; // 添加字符串终止符
    printf("\n");
}

void loginUser()
{
    system("cls");
    printf("XF二手市场系统 -- 登录\n");

    char username[20];
    User *user = NULL;
    printf("输入用户名: ");
    for (;;)
    {
        scanf("%s", username);
        user = findUserByUsername(username);
        if (user != NULL)
        {
            break;
        }
        printf("用户名不存在, 请重新输入: ");
    }

    char password[20];
    printf("输入密码: ");
    inputPassword(password);
    if (strcmp(user->password, password) != 0)
    {
        printf("密码错误\n");
    }
    else
    {
        currentUser = user;
        printf("登录成功\n");
    }
    _sleep(500);
}

void mainMenu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("\n==== 欢迎使用XF二手市场系统 ====\n");
        printf("1. 注册\n2. 登录\n0. 退出\n选择操作: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            if (currentUser != NULL)
            {
                currentUser->isAdmin ? adminMenu() : userMenu();
                currentUser = NULL;
            }
            break;
        case 0:
            printf("欢迎下次光临。\n");
            break;
        default:
            printf("无效选项。\n");
            _sleep(500);
        }
    }
}

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
        printf("\nXF�����г�ϵͳ -- �û��˵�\n");
        printf("1. ��Ʒ�б�\n");
        printf("2. ������Ʒ\n");
        printf("3. �ҵķ���\n");
        printf("4. �ҵĹ���\n");
        printf("0. �˳���¼\n");
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
            printf("��Чѡ�\n");
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
        printf("\nXF�����г�ϵͳ -- ����Ա�˵�\n");
        printf("1. ��Ʒ����\n");
        printf("2. �û�����\n");
        printf("3. ���۹���\n");
        printf("4. ��������\n");
        printf("0. �˳���¼\n");
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
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

void registerUser()
{
    system("cls");
    printf("XF�����г�ϵͳ -- ע��\n");

    User newUser;
    printf("�����û���: ");
    for (;;)
    {
        scanf("%s", newUser.username);
        User *existUser = findUserByUsername(newUser.username);
        if (existUser == NULL)
        {
            break;
        }
        printf("�û����Ѵ��ڣ�����������: ");
    }
    printf("��������: ");
    scanf("%s", newUser.password);
    if (addUser(newUser))
    {
        printf("ע��ɹ���\n");
    }
    else
    {
        printf("ע��ʧ�ܣ�\n");
    }
    _sleep(500);
}

void inputPassword(char *password)
{
    char ch;
    int index = 0;

    while (1)
    {
        ch = _getch(); // ��ȡһ���ַ�������ʾ
        if (ch == '\r')
        { // �س���������
            break;
        }
        else if (ch == '\b')
        { // �˸��
            if (index > 0)
            {
                index--;
                printf("\b \b"); // ɾ����ʾ�� *
            }
        }
        else if (index < 19 && ch >= 32 && ch <= 126)
        { // �������볤��
            password[index++] = ch;
            printf("*");
        }
    }

    password[index] = '\0'; // ����ַ�����ֹ��
    printf("\n");
}

void loginUser()
{
    system("cls");
    printf("XF�����г�ϵͳ -- ��¼\n");

    char username[20];
    User *user = NULL;
    printf("�����û���: ");
    for (;;)
    {
        scanf("%s", username);
        user = findUserByUsername(username);
        if (user != NULL)
        {
            break;
        }
        printf("�û���������, ����������: ");
    }

    char password[20];
    printf("��������: ");
    inputPassword(password);
    if (strcmp(user->password, password) != 0)
    {
        printf("�������\n");
    }
    else
    {
        currentUser = user;
        printf("��¼�ɹ�\n");
    }
    _sleep(500);
}

void mainMenu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("\n==== ��ӭʹ��XF�����г�ϵͳ ====\n");
        printf("1. ע��\n2. ��¼\n0. �˳�\nѡ�����: ");
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
            printf("��ӭ�´ι��١�\n");
            break;
        default:
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

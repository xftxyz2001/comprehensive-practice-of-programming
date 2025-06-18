#include "menu.h"

User *currentUser;

int buyProduct(Product *product)
{
    Order o;
    o.userID = currentUser->userID;
    o.productID = product->productID;
    o.ownerID = product->ownerID;
    strcpy(o.name, product->name);
    strcpy(o.description, product->description);
    o.price = product->price;
    if (addOrder(o))
    {
        product->isSold = 1;
        return 1;
    }
    return 0;
}

void productDetail(Product *product)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��Ʒ����\n");
        printf("��Ʒ����%s\n", product->name);
        printf("��Ʒ������%s\n", product->description);
        printf("��Ʒ�۸�%.2f\n", product->price);
        User *owner = findUserByID(product->ownerID);
        printf("�����ߣ�%s\n", owner ? owner->username : "?");
        printf("״̬��%s\n", product->isSold ? "�۳�" : "����");

        // TODO: չʾ����

        printf("1. ����\n");
        printf("2. ����\n");
        printf("0. ����\n");
        printf("������: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\nȷ��Ҫ�������Ʒ��(Y/N): ");
            scanf(" %c", &confirm); // ǰ��ӿո�����ǰһ���������µĻ��з�

            if (confirm == 'Y' || confirm == 'y')
            {
                if (buyProduct(product))
                {
                    printf("����ɹ���\n");
                    _sleep(500);
                    return; // ������һ��
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("��ȡ����\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 2:
            // TODO: ����
            break;
        case 0:
            break;
        default:
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

void showProductList()
{
    ProductList *products = getOnSaleProductList();
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��Ʒ�б�\n");
        printf("��ƷID\t��Ʒ��\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n�����ӦID�鿴��Ʒ ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Product *p = NULL;
        for (int i = 0; i < products->size; i++)
        {
            if (products->data[i].productID == choice)
            {
                p = &(products->data[i]);
                break;
            }
        }
        if (p == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        productDetail(p);
    }
}

void publishProduct()
{
    system("cls");
    printf("XFѧУ�����г�����ϵͳ -- ��Ʒ����\n");

    Product product;
    printf("������Ʒ��: ");
    scanf("%s", product.name);
    printf("����۸�: ");
    scanf("%lf", product.price);
    printf("��������: ");
    scanf("%s", product.description);

    product.ownerID = currentUser->userID;
    product.isSold = 0;
    product.createTime = time(NULL);
    if (addProduct(product))
    {
        printf("�����ɹ���\n");
    }
    else
    {
        printf("����ʧ�ܣ�\n");
    }
    _sleep(500);
}

void myPublish()
{
    ProductList *products = getMyPublishProductList(currentUser->userID);
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- �ҵķ���\n");
        printf("��ƷID\t��Ʒ��\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n�����ӦID�鿴��Ʒ ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Product *p = NULL;
        for (int i = 0; i < products->size; i++)
        {
            if (products->data[i].productID == choice)
            {
                p = &(products->data[i]);
                break;
            }
        }
        if (p == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        productDetail(p);
    }
}

void orderDetail(Order *order)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��������\n");
        printf("��Ʒ����%s\n", order->name);
        printf("��Ʒ������%s\n", order->description);
        printf("��Ʒ�۸�%.2f\n", order->price);
        User *owner = findUserByID(order->ownerID);
        printf("�����ߣ�%s\n", owner ? owner->username : "?");
        User *buyer = findUserByID(order->userID);
        printf("�����ߣ�%s\n", buyer ? buyer->username : "?");

        printf("1. ɾ��\n");
        printf("0. ����\n");
        printf("������: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\nȷ��Ҫɾ���ö�����(Y/N): ");
            scanf(" %c", &confirm); // ǰ��ӿո�����ǰһ���������µĻ��з�

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteOrderByID(order->orderID))
                {
                    printf("ɾ���ɹ���\n");
                    _sleep(500);
                    return; // ������һ��
                }
                else
                {
                    printf("ɾ��ʧ�ܡ�\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("��ȡ����\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 0:
            break;
        default:
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

void myPurchase()
{
    OrderList *orders = getMyPurchaseList(currentUser->userID);
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- �ҵĹ���\n");
        printf("����ID\t��Ʒ��\n");
        for (int i = 0; i < orders->size; i++)
        {
            Order o = orders->data[i];
            printf("%d\t%s\n", o.orderID, o.name);
        }
        printf("\n�����ӦID�鿴���� ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Order *o = NULL;
        for (int i = 0; i < orders->size; i++)
        {
            if (orders->data[i].orderID == choice)
            {
                o = &(orders->data[i]);
                break;
            }
        }
        if (o == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        orderDetail(o);
    }
}

void productManagement()
{
    ProductList *products = getProductList();
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��Ʒ����\n");
        printf("��ƷID\t��Ʒ��\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n�����ӦID�鿴��Ʒ ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Product *p = NULL;
        for (int i = 0; i < products->size; i++)
        {
            if (products->data[i].productID == choice)
            {
                p = &(products->data[i]);
                break;
            }
        }
        if (p == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        productDetail(p);
    }
}

void userDetail(User *user)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- �û�����\n");
        printf("�û�����%s\n", user->username);
        printf("���룺%s\n", user->password);
        printf("����Ա��%s\n", user->isAdmin ? "��" : "��");

        printf("1. ɾ��\n");
        printf("2. ��Ϊ����Ա\n");
        printf("0. ����\n");
        printf("������: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\nȷ��Ҫɾ�����û���(Y/N): ");
            scanf(" %c", &confirm); // ǰ��ӿո�����ǰһ���������µĻ��з�

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteUserByID(user->userID))
                {
                    printf("ɾ���ɹ���\n");
                    _sleep(500);
                    return; // ������һ��
                }
                else
                {
                    printf("ɾ��ʧ�ܡ�\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("��ȡ����\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 2:
            user->isAdmin = 1;
            printf("����Ϊ����Ա��\n");
            _sleep(500);
            break;
        case 0:
            break;
        default:
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

void userManagement()
{
    UserList *users = getUserList();
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- �û�����\n");
        printf("�û�ID\t�û���\n");
        for (int i = 0; i < users->size; i++)
        {
            User u = users->data[i];
            printf("%d\t%s\n", u.userID, u.username);
        }
        printf("\n�����ӦID�鿴�û� ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        User *u = NULL;
        for (int i = 0; i < users->size; i++)
        {
            if (users->data[i].userID == choice)
            {
                u = &(users->data[i]);
                break;
            }
        }
        if (u == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        userDetail(u);
    }
}

void messageDetail(Message *message)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��������\n");
        User *user = findUserByID(message->userID);
        printf("�û�����%s\n", user ? user->username : "?");
        Product *product = findProductByID(message->productID);
        printf("��Ʒ����%s\n", product ? product->name : "?");
        printf("�������ݣ�%s\n", message->message);

        printf("1. ɾ��\n");
        printf("0. ����\n");
        printf("������: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\nȷ��Ҫɾ����������(Y/N): ");
            scanf(" %c", &confirm); // ǰ��ӿո�����ǰһ���������µĻ��з�

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteMessageByID(message->messageID))
                {
                    printf("ɾ���ɹ���\n");
                    _sleep(500);
                    return; // ������һ��
                }
                else
                {
                    printf("ɾ��ʧ�ܡ�\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("��ȡ����\n");
                _sleep(500);
            }
            break;
        }
        case 0:
            break;
        default:
            printf("��Чѡ�\n");
            _sleep(500);
        }
    }
}

void messageManagement()
{
    MessageList *messages = getMessageList();
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ���۹���\n");
        printf("����ID\t��������\n");
        for (int i = 0; i < messages->size; i++)
        {
            Message m = messages->data[i];
            printf("%d\t%s\n", m.messageID, m.message);
        }
        printf("\n�����ӦID�鿴���� ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Message *m = NULL;
        for (int i = 0; i < messages->size; i++)
        {
            if (messages->data[i].messageID == choice)
            {
                m = &(messages->data[i]);
                break;
            }
        }
        if (m == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        messageDetail(m);
    }
}

void orderManagement()
{
    OrderList *orders = getOrderList();
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("XFѧУ�����г�����ϵͳ -- ��������\n");
        printf("����ID\t��Ʒ��\n");
        for (int i = 0; i < orders->size; i++)
        {
            Order o = orders->data[i];
            printf("%d\t%s\n", o.orderID, o.name);
        }
        printf("\n�����ӦID�鿴���� ����0����: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        Order *o = NULL;
        for (int i = 0; i < orders->size; i++)
        {
            if (orders->data[i].orderID == choice)
            {
                o = &(orders->data[i]);
                break;
            }
        }
        if (o == NULL)
        {
            printf("��Чѡ�\n");
            _sleep(500);
            continue;
        }
        orderDetail(o);
    }
}

void userMenu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        printf("\nXFѧУ�����г�����ϵͳ -- �û��˵�\n");
        printf("1. ��Ʒ�б�\n");
        printf("2. ������Ʒ\n");
        printf("3. �ҵķ���\n");
        printf("4. �ҵĹ���\n");
        printf("0. �˳���¼\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            showProductList();
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
        printf("\nXFѧУ�����г�����ϵͳ -- ����Ա�˵�\n");
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
    printf("XFѧУ�����г�����ϵͳ -- ע��\n");

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
    newUser.isAdmin = 0;
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
    printf("XFѧУ�����г�����ϵͳ -- ��¼\n");

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
        printf("\n==== ��ӭʹ��XFѧУ�����г�����ϵͳ ====\n");
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

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
        printf("XF学校二手市场交易系统 -- 商品详情\n");
        printf("商品名：%s\n", product->name);
        printf("商品描述：%s\n", product->description);
        printf("商品价格：%.2f\n", product->price);
        User *owner = findUserByID(product->ownerID);
        printf("发布者：%s\n", owner ? owner->username : "?");
        printf("状态：%s\n", product->isSold ? "售出" : "在售");

        // TODO: 展示评论

        printf("1. 购买\n");
        printf("2. 评论\n");
        printf("0. 返回\n");
        printf("请输入: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\n确认要购买该商品吗？(Y/N): ");
            scanf(" %c", &confirm); // 前面加空格跳过前一个输入留下的换行符

            if (confirm == 'Y' || confirm == 'y')
            {
                if (buyProduct(product))
                {
                    printf("购买成功。\n");
                    _sleep(500);
                    return; // 返回上一层
                }
                else
                {
                    printf("购买失败。\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("已取消。\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 2:
            // TODO: 评论
            break;
        case 0:
            break;
        default:
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 商品列表\n");
        printf("商品ID\t商品名\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n输入对应ID查看商品 输入0返回: ");
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
            printf("无效选项。\n");
            _sleep(500);
            continue;
        }
        productDetail(p);
    }
}

void publishProduct()
{
    system("cls");
    printf("XF学校二手市场交易系统 -- 商品发布\n");

    Product product;
    printf("输入商品名: ");
    scanf("%s", product.name);
    printf("输入价格: ");
    scanf("%lf", product.price);
    printf("输入描述: ");
    scanf("%s", product.description);

    product.ownerID = currentUser->userID;
    product.isSold = 0;
    product.createTime = time(NULL);
    if (addProduct(product))
    {
        printf("发布成功！\n");
    }
    else
    {
        printf("发布失败！\n");
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
        printf("XF学校二手市场交易系统 -- 我的发布\n");
        printf("商品ID\t商品名\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n输入对应ID查看商品 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 订单详情\n");
        printf("商品名：%s\n", order->name);
        printf("商品描述：%s\n", order->description);
        printf("商品价格：%.2f\n", order->price);
        User *owner = findUserByID(order->ownerID);
        printf("发布者：%s\n", owner ? owner->username : "?");
        User *buyer = findUserByID(order->userID);
        printf("购买者：%s\n", buyer ? buyer->username : "?");

        printf("1. 删除\n");
        printf("0. 返回\n");
        printf("请输入: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\n确认要删除该订单吗？(Y/N): ");
            scanf(" %c", &confirm); // 前面加空格跳过前一个输入留下的换行符

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteOrderByID(order->orderID))
                {
                    printf("删除成功。\n");
                    _sleep(500);
                    return; // 返回上一层
                }
                else
                {
                    printf("删除失败。\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("已取消。\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 0:
            break;
        default:
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 我的购买\n");
        printf("订单ID\t商品名\n");
        for (int i = 0; i < orders->size; i++)
        {
            Order o = orders->data[i];
            printf("%d\t%s\n", o.orderID, o.name);
        }
        printf("\n输入对应ID查看订单 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 商品管理\n");
        printf("商品ID\t商品名\n");
        for (int i = 0; i < products->size; i++)
        {
            Product p = products->data[i];
            printf("%d\t%s\n", p.productID, p.name);
        }
        printf("\n输入对应ID查看商品 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 用户详情\n");
        printf("用户名：%s\n", user->username);
        printf("密码：%s\n", user->password);
        printf("管理员：%s\n", user->isAdmin ? "是" : "否");

        printf("1. 删除\n");
        printf("2. 设为管理员\n");
        printf("0. 返回\n");
        printf("请输入: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\n确认要删除该用户吗？(Y/N): ");
            scanf(" %c", &confirm); // 前面加空格跳过前一个输入留下的换行符

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteUserByID(user->userID))
                {
                    printf("删除成功。\n");
                    _sleep(500);
                    return; // 返回上一层
                }
                else
                {
                    printf("删除失败。\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("已取消。\n");
                _sleep(500);
            }
            break;
        }
        break;
        case 2:
            user->isAdmin = 1;
            printf("已设为管理员。\n");
            _sleep(500);
            break;
        case 0:
            break;
        default:
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 用户管理\n");
        printf("用户ID\t用户名\n");
        for (int i = 0; i < users->size; i++)
        {
            User u = users->data[i];
            printf("%d\t%s\n", u.userID, u.username);
        }
        printf("\n输入对应ID查看用户 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 评论详情\n");
        User *user = findUserByID(message->userID);
        printf("用户名：%s\n", user ? user->username : "?");
        Product *product = findProductByID(message->productID);
        printf("商品名：%s\n", product ? product->name : "?");
        printf("评论内容：%s\n", message->message);

        printf("1. 删除\n");
        printf("0. 返回\n");
        printf("请输入: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char confirm;
            printf("\n确认要删除该评论吗？(Y/N): ");
            scanf(" %c", &confirm); // 前面加空格跳过前一个输入留下的换行符

            if (confirm == 'Y' || confirm == 'y')
            {
                if (deleteMessageByID(message->messageID))
                {
                    printf("删除成功。\n");
                    _sleep(500);
                    return; // 返回上一层
                }
                else
                {
                    printf("删除失败。\n");
                    _sleep(500);
                }
            }
            else
            {
                printf("已取消。\n");
                _sleep(500);
            }
            break;
        }
        case 0:
            break;
        default:
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 评论管理\n");
        printf("评论ID\t评论内容\n");
        for (int i = 0; i < messages->size; i++)
        {
            Message m = messages->data[i];
            printf("%d\t%s\n", m.messageID, m.message);
        }
        printf("\n输入对应ID查看详情 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("XF学校二手市场交易系统 -- 订单管理\n");
        printf("订单ID\t商品名\n");
        for (int i = 0; i < orders->size; i++)
        {
            Order o = orders->data[i];
            printf("%d\t%s\n", o.orderID, o.name);
        }
        printf("\n输入对应ID查看订单 输入0返回: ");
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
            printf("无效选项。\n");
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
        printf("\nXF学校二手市场交易系统 -- 用户菜单\n");
        printf("1. 商品列表\n");
        printf("2. 发布商品\n");
        printf("3. 我的发布\n");
        printf("4. 我的购买\n");
        printf("0. 退出登录\n");
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
        printf("\nXF学校二手市场交易系统 -- 管理员菜单\n");
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
    printf("XF学校二手市场交易系统 -- 注册\n");

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
    newUser.isAdmin = 0;
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
    printf("XF学校二手市场交易系统 -- 登录\n");

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
        printf("\n==== 欢迎使用XF学校二手市场交易系统 ====\n");
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

#include "store.h"

#define INITIAL_CAPACITY 10

UserList *userList = NULL;
ProductList *productList = NULL;
MessageList *messageList = NULL;
OrderList *orderList = NULL;

UserList *createUserList()
{
    UserList *list = (UserList *)malloc(sizeof(UserList));
    list->capacity = INITIAL_CAPACITY;
    list->data = (User *)malloc(sizeof(User) * INITIAL_CAPACITY);
    if (list->data == NULL)
    {
        return NULL;
    }
    list->size = 0;
    return list;
}

int ensureUserCapacity()
{
    if (userList->size >= userList->capacity)
    {
        userList->capacity = userList->capacity * 1.5 + 1;
        User *newData = realloc(userList->data, sizeof(User) * userList->capacity);
        if (newData == NULL)
        {
            return 0;
        }
        userList->data = newData;
    }
    return 1;
}

int generateNextUserID()
{
    int maxID = 0;
    for (int i = 0; i < userList->size; i++)
    {
        if (userList->data[i].userID > maxID)
        {
            maxID = userList->data[i].userID;
        }
    }
    return maxID + 1;
}

int addUser(User u)
{
    ensureUserCapacity();
    u.userID = generateNextUserID();
    userList->data[userList->size++] = u;
    return 1;
}

int deleteUserByID(int userID)
{
    for (int i = 0; i < userList->size; i++)
    {
        if (userList->data[i].userID == userID)
        {
            for (int j = i; j < userList->size - 1; j++)
            {
                userList->data[j] = userList->data[j + 1];
            }
            userList->size--;
            return 1;
        }
    }
    return 0;
}

UserList *getUserList()
{
    return userList;
}

User *findUserByID(int userID)
{
    for (int i = 0; i < userList->size; i++)
    {
        if (userList->data[i].userID == userID)
        {
            return &(userList->data[i]);
        }
    }
    return NULL;
}

User *findUserByUsername(char *username)
{
    for (int i = 0; i < userList->size; i++)
    {
        if (strcmp(userList->data[i].username, username) == 0)
        {
            return &(userList->data[i]);
        }
    }
    return NULL;
}

int loadUsers()
{
    FILE *file = fopen("users.bin", "rb");
    if (file == NULL)
    {
        return 0;
    }
    User u;
    while (fread(&u, sizeof(User), 1, file))
    {
        addUser(u);
    }
    fclose(file);
    return 1;
}

int saveUsers()
{
    FILE *file = fopen("users.bin", "wb");
    if (file == NULL)
    {
        return 0;
    }
    for (int i = 0; i < userList->size; i++)
    {
        fwrite(&userList->data[i], sizeof(User), 1, file);
    }
    fclose(file);
    return 1;
}

int freeUserList()
{
    free(userList->data);
    userList->data = NULL;

    userList->size = 0;
    userList->capacity = 0;
    return 1;
}

ProductList *createProductList()
{
    ProductList *list = (ProductList *)malloc(sizeof(ProductList));
    list->capacity = INITIAL_CAPACITY;
    list->data = (Product *)malloc(sizeof(Product) * INITIAL_CAPACITY);
    if (list->data == NULL)
    {
        return NULL;
    }
    list->size = 0;
    return list;
}

int ensureProductCapacity()
{
    if (productList->size >= productList->capacity)
    {
        productList->capacity = productList->capacity * 1.5 + 1;
        Product *newData = realloc(productList->data, sizeof(Product) * productList->capacity);
        if (newData == NULL)
        {
            return 0;
        }
        productList->data = newData;
    }
    return 1;
}

int generateNextProductID()
{
    int maxID = 0;
    for (int i = 0; i < productList->size; i++)
    {
        if (productList->data[i].productID > maxID)
        {
            maxID = productList->data[i].productID;
        }
    }
    return maxID + 1;
}

int addProduct(Product p)
{
    ensureProductCapacity();
    p.productID = generateNextProductID();
    productList->data[productList->size++] = p;
    return 1;
}

int deleteProductByID(int productID)
{
    for (int i = 0; i < productList->size; i++)
    {
        if (productList->data[i].productID == productID)
        {
            for (int j = i; j < productList->size - 1; j++)
            {
                productList->data[j] = productList->data[j + 1];
            }
            productList->size--;
            return 1;
        }
    }
    return 0;
}

ProductList *getProductList()
{
    return productList;
}

ProductList *getOnSaleProductList()
{
    ProductList *list = createProductList();
    for (int i = 0; i < productList->size; i++)
    {
        if (productList->data[i].isSold == 0)
        {
            ensureProductCapacity(list);
            list->data[list->size++] = productList->data[i];
        }
    }
    return list;
}

ProductList *getMyPublishProductList(int userID)
{
    ProductList *list = createProductList();
    for (int i = 0; i < productList->size; i++)
    {
        if (productList->data[i].ownerID == userID)
        {
            ensureProductCapacity(list);
            list->data[list->size++] = productList->data[i];
        }
    }
    return list;
}

Product *findProductByID(int productID)
{
    for (int i = 0; i < productList->size; i++)
    {
        if (productList->data[i].productID == productID)
        {
            return &(productList->data[i]);
        }
    }
    return NULL;
}

int loadProducts()
{
    FILE *file = fopen("products.bin", "rb");
    if (file == NULL)
    {
        return 0;
    }
    Product p;
    while (fread(&p, sizeof(Product), 1, file))
    {
        addProduct(p);
    }
    fclose(file);
    return 1;
}

int saveProducts()
{
    FILE *file = fopen("products.bin", "wb");
    if (file == NULL)
    {

        return 0;
    }
    for (int i = 0; i < productList->size; i++)
    {
        fwrite(&productList->data[i], sizeof(Product), 1, file);
    }
    fclose(file);
    return 1;
}

int freeProductList()
{
    free(productList->data);
    productList->data = NULL;

    productList->size = 0;
    productList->capacity = 0;
    return 1;
}

MessageList *createMessageList()
{
    MessageList *list = (MessageList *)malloc(sizeof(MessageList));
    list->capacity = INITIAL_CAPACITY;
    list->data = (Message *)malloc(sizeof(Message) * INITIAL_CAPACITY);
    if (list->data == NULL)
    {
        return NULL;
    }
    list->size = 0;
    return list;
}

int ensureMessageCapacity()
{
    if (messageList->size >= messageList->capacity)
    {
        messageList->capacity = messageList->capacity * 1.5 + 1;
        Message *newData = realloc(messageList->data, sizeof(Message) * messageList->capacity);
        if (newData == NULL)
        {
            return 0;
        }
        messageList->data = newData;
    }
    return 1;
}

int generateNextMessageID()
{
    int maxID = 0;
    for (int i = 0; i < messageList->size; i++)
    {
        if (messageList->data[i].messageID > maxID)
        {
            maxID = messageList->data[i].messageID;
        }
    }
    return maxID + 1;
}

int addMessage(Message m)
{
    ensureMessageCapacity();
    m.messageID = generateNextMessageID();
    messageList->data[messageList->size++] = m;
    return 1;
}

int deleteMessageByID(int messageID)
{
    for (int i = 0; i < messageList->size; i++)
    {
        if (messageList->data[i].messageID == messageID)
        {
            for (int j = i; j < messageList->size - 1; j++)
            {
                messageList->data[j] = messageList->data[j + 1];
            }
            messageList->size--;
            return 1;
        }
    }
    return 0;
}

MessageList *getMessageList()
{
    return messageList;
}

int loadMessages()
{
    FILE *file = fopen("messages.bin", "rb");
    if (file == NULL)
    {
        return 0;
    }
    Message m;
    while (fread(&m, sizeof(Message), 1, file))
    {
        addMessage(m);
    }
    fclose(file);
    return 1;
}

int saveMessages()
{
    FILE *file = fopen("messages.bin", "wb");
    if (file == NULL)
    {
        return 0;
    }
    for (int i = 0; i < messageList->size; i++)
    {
        fwrite(&messageList->data[i], sizeof(Message), 1, file);
    }
    fclose(file);
    return 1;
}

int freeMessageList()
{
    free(messageList->data);
    messageList->data = NULL;

    messageList->size = 0;
    messageList->capacity = 0;
    return 1;
}

OrderList *createOrderList()
{
    OrderList *list = (OrderList *)malloc(sizeof(OrderList));
    list->capacity = INITIAL_CAPACITY;
    list->data = (Order *)malloc(sizeof(Order) * INITIAL_CAPACITY);
    if (list->data == NULL)
    {
        return NULL;
    }
    list->size = 0;
    return list;
}

int ensureOrderCapacity()
{
    if (orderList->size >= orderList->capacity)
    {
        orderList->capacity = orderList->capacity * 1.5 + 1;
        Order *newData = realloc(orderList->data, sizeof(Order) * orderList->capacity);
        if (newData == NULL)
        {
            return 0;
        }
        orderList->data = newData;
    }
    return 1;
}

int generateNextOrderID()
{
    int maxID = 0;
    for (int i = 0; i < orderList->size; i++)
    {
        if (orderList->data[i].orderID > maxID)
        {
            maxID = orderList->data[i].orderID;
        }
    }
    return maxID + 1;
}

int addOrder(Order o)
{
    ensureOrderCapacity();
    o.orderID = generateNextOrderID();
    orderList->data[orderList->size++] = o;
    return 1;
}

int deleteOrderByID(int orderID)
{
    for (int i = 0; i < orderList->size; i++)
    {
        if (orderList->data[i].orderID == orderID)
        {
            for (int j = i; j < orderList->size - 1; j++)
            {
                orderList->data[j] = orderList->data[j + 1];
            }
            orderList->size--;
            return 1;
        }
    }
    return 0;
}

OrderList *getOrderList()
{
    return orderList;
}

OrderList *getMyPurchaseList(int userID)
{
    OrderList *list = createOrderList();
    for (int i = 0; i < orderList->size; i++)
    {
        if (orderList->data[i].userID == userID)
        {
            ensureOrderCapacity(list);
            list->data[list->size++] = orderList->data[i];
        }
    }
    return list;
}

int loadOrders()
{
    FILE *file = fopen("orders.bin", "rb");
    if (file == NULL)
    {
        return 0;
    }
    Order o;
    while (fread(&o, sizeof(Order), 1, file))
    {
        addOrder(o);
    }
    fclose(file);
    return 1;
}

int saveOrders()
{
    FILE *file = fopen("orders.bin", "wb");
    if (file == NULL)
    {
        return 0;
    }
    for (int i = 0; i < orderList->size; i++)
    {
        fwrite(&orderList->data[i], sizeof(Order), 1, file);
    }
    fclose(file);
    return 1;
}

int freeOrderList()
{
    free(orderList->data);
    orderList->data = NULL;

    orderList->size = 0;
    orderList->capacity = 0;
    return 1;
}

int initStore()
{
    printf("Мгдижа...");
    userList = createUserList();
    loadUsers();

    productList = createProductList();
    loadProducts();

    messageList = createMessageList();
    loadMessages();

    orderList = createOrderList();
    loadOrders();
    return 1;
}

int destroyStore()
{
    saveUsers();
    freeUserList(&userList);

    saveProducts();
    freeProductList(&productList);

    saveMessages();
    freeMessageList(&messageList);

    saveOrders();
    freeOrderList(&orderList);
    return 1;
}

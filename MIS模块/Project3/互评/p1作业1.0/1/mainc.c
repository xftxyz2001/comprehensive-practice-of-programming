#include "main.h"
#include "feedback.h"

// 检查并扩容
static void CheckCapacity(Userlist* ps) {
    if (ps->size == ps->capacity) {
        User* newdata = realloc(ps->data, (ps->capacity + 2) * sizeof(User));
        if (newdata != NULL) {
            ps->data = newdata;
            ps->capacity += 2;
            printf("增容成功，当前容量: %d\n", ps->capacity);
        }
        else {
            printf("内存不足，无法扩容！\n");
            exit(1); // 严重错误直接退出
        }
    }
}

// 初始化系统
void initSystem(Userlist* ps) {
    ps->data = (User*)malloc(DEFAULT_SZ * sizeof(User));
    if (ps->data == NULL) {
        printf("内存分配失败: %s\n", strerror(errno));
        exit(1);
    }
    ps->size = 0;
    ps->capacity = DEFAULT_SZ;
    printf("系统初始化成功，初始容量: %d\n", DEFAULT_SZ);
}

// 加载用户数据
void Loadsystem(Userlist* ps) {
    User tmp = { 0 };
    FILE* co = fopen(DATA_FILE, "r");
    if (co == NULL) {
        printf("无法打开用户文件: %s\n", strerror(errno));
        return;
    }

    while (fscanf(co, "%d %s %s", &tmp.id, tmp.name, tmp.password) == 3) {
        CheckCapacity(ps);
        ps->data[ps->size] = tmp;
        ps->size++;
    }
    fclose(co);
    co = NULL;
    printf("成功加载 %d 个用户数据\n", ps->size);
}

// 密码输入（隐藏显示）
static void stupass(char szUserPass[PASS + 1]) {
    printf("\n请输入密码：\n");
    int i = 0;
    char ch;
    while (i < PASS) {
        ch = _getch();
        if (ch == 8 && i > 0) { // 退格处理
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
            continue;
        }
        if (ch == 13) break;    // 回车结束
        szUserPass[i] = ch;
        putchar('*');
        i++;
    }
    szUserPass[i] = '\0';
    printf("\n");
}

static int findname(Userlist* ps, int userid) {
    int i = 0;
    for (i = 0; i < ps->size; i++) {
        if (ps->data[i].id == userid) {
            return i;
        }
    }
    return -1;
}

// 登录功能
void userLogin(Userlist* ps) {
    int userid;
    printf("请输入用户ID: ");
    if (scanf("%d", &userid) != 1) {
        while (getchar() != '\n');
        printf("无效的输入，请重新输入。\n");
        printf("按任意键继续...\n");
        _getch();
        return;
    }

    int ret = findname(ps, userid);
    if (ret == -1) {
        printf("该用户不存在;\n");
        printf("按任意键继续...\n");
        _getch();
    }
    else {
        char szUserPass[PASS + 1] = { 0 };
        stupass(szUserPass);

        if (strcmp(ps->data[ret].password, szUserPass) == 0) {
            if (userid >= 1000 && userid < 2000) {
                printf("欢迎学生用户 %s\n", ps->data[ret].name);
                studentMenu(ps->data[ret].id);
            }
            else if (userid >= 2000) {
                printf("欢迎商家用户 %s\n", ps->data[ret].name);
                merchantMenu(ps->data[ret].id);
            }
            else if( userid < 1000) {
                printf("欢迎管理员用户 %s\n", ps->data[ret].name);
                showMainMenu();
            }
			else
            {
                printf("未知用户类型！\n");
            }
        }
        else {
            printf("密码错误，请重试。\n");
            printf("按任意键继续...\n");
            _getch();
        }
    }
}

// 学生注册
static void studentRegister(Userlist* ps) {
    // 确保有足够空间
    CheckCapacity(ps);

    int num = 1000 + ps->size;
    printf("你的账号是: %d\n", num);
    printf("请输入姓名：\n");
    if (scanf("%s", ps->data[ps->size].name) != 1) {
        while (getchar() != '\n');
        printf("输入无效\n");
        return;
    }

    char szUserPass[PASS + 1] = { 0 };
    stupass(szUserPass);

    ps->data[ps->size].id = num;
    strcpy(ps->data[ps->size].password, szUserPass);
    ps->size++;

    printf("学生注册成功！\n");
    saveData(ps); // 注册后保存数据
}

// 商家注册（修复版）
static void businessRegister(Userlist* ps) {
    // 关键修复：先检查扩容，再使用ps->data[ps->size]
    CheckCapacity(ps);

    int num = 2000 + ps->size;
    printf("你的账号是: %d\n", num);
    printf("请输入姓名：\n");
    if (scanf("%s", ps->data[ps->size].name) != 1) {
        while (getchar() != '\n');
        printf("输入无效\n");
        return;
    }

    char szUserPass[PASS + 1] = { 0 };
    stupass(szUserPass);

    ps->data[ps->size].id = num;
    strcpy(ps->data[ps->size].password, szUserPass);
    ps->size++;

    printf("商家注册成功！\n");
    saveData(ps); // 注册后保存数据
}

// 注册入口
void userRegister(Userlist* ps) {
    int choice;
    while (1) {
        printf("\n===== 用户注册系统 =====\n");
        printf("1. 学生注册\n");
        printf("2. 商家注册\n");
        printf("3. 退出\n");
        printf("请选择功能（1-3）：");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("输入无效，请重新选择：");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1: studentRegister(ps); break;
        case 2: businessRegister(ps); break;
        case 3: printf("已退出注册系统。\n"); return;
        default: printf("无效选择！\n");
        }
    }
}

// 保存数据到文件
void saveData(Userlist* ps) {
    FILE* co = fopen(DATA_FILE, "w");
    if (co == NULL) {
        printf("无法打开文件保存用户数据: %s\n", strerror(errno));
        return;
    }

    // 写入数据
    for (int i = 0; i < ps->size; i++) {
        if (fprintf(co, "%d %s %s\n", ps->data[i].id, ps->data[i].name, ps->data[i].password) < 0) {
            printf("写入数据失败\n");
            break;
        }
    }
    fclose(co);
    co = NULL;
    printf("用户数据已保存到文件\n");
}
#include"main.h"

static void clear_screen()
{
#ifdef _WIN32
    system("cls");  // Windows系统
#else
    system("clear"); // Linux/Mac系统
#endif
}

int main()
{
    int choice = 0;
    Userlist ul;
    initSystem(&ul);   // 系统初始化
    Loadsystem(&ul); // 加载系统数据
    do
    {
        clear_screen();
        printf("欢迎使用CCEFS系统\n");
        printf("1. 登录\n");
        printf("2. 注册\n");
        printf("3. 退出\n");
        printf("请选择操作: ");
        if (scanf("%d", &choice) != 1) // 仅添加的检查
        {
            while (getchar() != '\n'); // 清除输入缓冲区
            printf("无效的输入，请重新输入。\n");
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen();
            userLogin(&ul); // 用户登录
            break;
        case 2:
            clear_screen();
            userRegister(&ul); // 用户注册
            break;
        case 3:
            printf("感谢使用CCEFS系统，再见！\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            printf("按任意键继续...\n");
            _getch();  // 等待用户按键
            break;
        }
    } while (choice != 3);    // 进入登录流程

    saveData(&ul);           // 退出前保存数据
    return 0;
}
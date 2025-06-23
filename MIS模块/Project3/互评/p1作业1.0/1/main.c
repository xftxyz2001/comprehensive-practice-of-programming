#include"main.h"

static void clear_screen()
{
#ifdef _WIN32
    system("cls");  // Windowsϵͳ
#else
    system("clear"); // Linux/Macϵͳ
#endif
}

int main()
{
    int choice = 0;
    Userlist ul;
    initSystem(&ul);   // ϵͳ��ʼ��
    Loadsystem(&ul); // ����ϵͳ����
    do
    {
        clear_screen();
        printf("��ӭʹ��CCEFSϵͳ\n");
        printf("1. ��¼\n");
        printf("2. ע��\n");
        printf("3. �˳�\n");
        printf("��ѡ�����: ");
        if (scanf("%d", &choice) != 1) // ����ӵļ��
        {
            while (getchar() != '\n'); // ������뻺����
            printf("��Ч�����룬���������롣\n");
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen();
            userLogin(&ul); // �û���¼
            break;
        case 2:
            clear_screen();
            userRegister(&ul); // �û�ע��
            break;
        case 3:
            printf("��лʹ��CCEFSϵͳ���ټ���\n");
            break;
        default:
            printf("��Ч��ѡ�����������롣\n");
            printf("�����������...\n");
            _getch();  // �ȴ��û�����
            break;
        }
    } while (choice != 3);    // �����¼����

    saveData(&ul);           // �˳�ǰ��������
    return 0;
}
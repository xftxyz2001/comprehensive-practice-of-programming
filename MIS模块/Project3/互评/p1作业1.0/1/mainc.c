#include "main.h"
#include "feedback.h"

// ��鲢����
static void CheckCapacity(Userlist* ps) {
    if (ps->size == ps->capacity) {
        User* newdata = realloc(ps->data, (ps->capacity + 2) * sizeof(User));
        if (newdata != NULL) {
            ps->data = newdata;
            ps->capacity += 2;
            printf("���ݳɹ�����ǰ����: %d\n", ps->capacity);
        }
        else {
            printf("�ڴ治�㣬�޷����ݣ�\n");
            exit(1); // ���ش���ֱ���˳�
        }
    }
}

// ��ʼ��ϵͳ
void initSystem(Userlist* ps) {
    ps->data = (User*)malloc(DEFAULT_SZ * sizeof(User));
    if (ps->data == NULL) {
        printf("�ڴ����ʧ��: %s\n", strerror(errno));
        exit(1);
    }
    ps->size = 0;
    ps->capacity = DEFAULT_SZ;
    printf("ϵͳ��ʼ���ɹ�����ʼ����: %d\n", DEFAULT_SZ);
}

// �����û�����
void Loadsystem(Userlist* ps) {
    User tmp = { 0 };
    FILE* co = fopen(DATA_FILE, "r");
    if (co == NULL) {
        printf("�޷����û��ļ�: %s\n", strerror(errno));
        return;
    }

    while (fscanf(co, "%d %s %s", &tmp.id, tmp.name, tmp.password) == 3) {
        CheckCapacity(ps);
        ps->data[ps->size] = tmp;
        ps->size++;
    }
    fclose(co);
    co = NULL;
    printf("�ɹ����� %d ���û�����\n", ps->size);
}

// �������루������ʾ��
static void stupass(char szUserPass[PASS + 1]) {
    printf("\n���������룺\n");
    int i = 0;
    char ch;
    while (i < PASS) {
        ch = _getch();
        if (ch == 8 && i > 0) { // �˸���
            putchar('\b');
            putchar(' ');
            putchar('\b');
            i--;
            continue;
        }
        if (ch == 13) break;    // �س�����
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

// ��¼����
void userLogin(Userlist* ps) {
    int userid;
    printf("�������û�ID: ");
    if (scanf("%d", &userid) != 1) {
        while (getchar() != '\n');
        printf("��Ч�����룬���������롣\n");
        printf("�����������...\n");
        _getch();
        return;
    }

    int ret = findname(ps, userid);
    if (ret == -1) {
        printf("���û�������;\n");
        printf("�����������...\n");
        _getch();
    }
    else {
        char szUserPass[PASS + 1] = { 0 };
        stupass(szUserPass);

        if (strcmp(ps->data[ret].password, szUserPass) == 0) {
            if (userid >= 1000 && userid < 2000) {
                printf("��ӭѧ���û� %s\n", ps->data[ret].name);
                studentMenu(ps->data[ret].id);
            }
            else if (userid >= 2000) {
                printf("��ӭ�̼��û� %s\n", ps->data[ret].name);
                merchantMenu(ps->data[ret].id);
            }
            else if( userid < 1000) {
                printf("��ӭ����Ա�û� %s\n", ps->data[ret].name);
                showMainMenu();
            }
			else
            {
                printf("δ֪�û����ͣ�\n");
            }
        }
        else {
            printf("������������ԡ�\n");
            printf("�����������...\n");
            _getch();
        }
    }
}

// ѧ��ע��
static void studentRegister(Userlist* ps) {
    // ȷ�����㹻�ռ�
    CheckCapacity(ps);

    int num = 1000 + ps->size;
    printf("����˺���: %d\n", num);
    printf("������������\n");
    if (scanf("%s", ps->data[ps->size].name) != 1) {
        while (getchar() != '\n');
        printf("������Ч\n");
        return;
    }

    char szUserPass[PASS + 1] = { 0 };
    stupass(szUserPass);

    ps->data[ps->size].id = num;
    strcpy(ps->data[ps->size].password, szUserPass);
    ps->size++;

    printf("ѧ��ע��ɹ���\n");
    saveData(ps); // ע��󱣴�����
}

// �̼�ע�ᣨ�޸��棩
static void businessRegister(Userlist* ps) {
    // �ؼ��޸����ȼ�����ݣ���ʹ��ps->data[ps->size]
    CheckCapacity(ps);

    int num = 2000 + ps->size;
    printf("����˺���: %d\n", num);
    printf("������������\n");
    if (scanf("%s", ps->data[ps->size].name) != 1) {
        while (getchar() != '\n');
        printf("������Ч\n");
        return;
    }

    char szUserPass[PASS + 1] = { 0 };
    stupass(szUserPass);

    ps->data[ps->size].id = num;
    strcpy(ps->data[ps->size].password, szUserPass);
    ps->size++;

    printf("�̼�ע��ɹ���\n");
    saveData(ps); // ע��󱣴�����
}

// ע�����
void userRegister(Userlist* ps) {
    int choice;
    while (1) {
        printf("\n===== �û�ע��ϵͳ =====\n");
        printf("1. ѧ��ע��\n");
        printf("2. �̼�ע��\n");
        printf("3. �˳�\n");
        printf("��ѡ���ܣ�1-3����");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("������Ч��������ѡ��");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1: studentRegister(ps); break;
        case 2: businessRegister(ps); break;
        case 3: printf("���˳�ע��ϵͳ��\n"); return;
        default: printf("��Чѡ��\n");
        }
    }
}

// �������ݵ��ļ�
void saveData(Userlist* ps) {
    FILE* co = fopen(DATA_FILE, "w");
    if (co == NULL) {
        printf("�޷����ļ������û�����: %s\n", strerror(errno));
        return;
    }

    // д������
    for (int i = 0; i < ps->size; i++) {
        if (fprintf(co, "%d %s %s\n", ps->data[i].id, ps->data[i].name, ps->data[i].password) < 0) {
            printf("д������ʧ��\n");
            break;
        }
    }
    fclose(co);
    co = NULL;
    printf("�û������ѱ��浽�ļ�\n");
}
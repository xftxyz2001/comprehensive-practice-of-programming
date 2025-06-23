#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX_VEHICLES 100
#define ADMIN_PASSWORD "administrators"
#define VISITOR_MAX_STAY 12
#define STUDENT_MAX_STAY 72
#define TEACHER_MAX_STAY 168
#define HOURLY_RATE 2
#define OVERTIME_RATE 5
#define MAX_FEE 500
#define MAX_INPUT_LENGTH 100

// ANSI 转义序列颜色定义
#define ANSI_COLOR_RESET "\x1B[0m"
#define ANSI_COLOR_GREEN "\x1B[32m"
#define ANSI_COLOR_YELLOW "\x1B[33m"
#define ANSI_COLOR_BLUE "\x1B[34m"

typedef struct {
    char license_plate[20];
    char owner_name[50];
    int entry_time;
    int parking_space;
    float balance;
    int user_type; // 0: visitor, 1: student, 2: teacher
} Vehicle;

Vehicle vehicles[MAX_VEHICLES];
int vehicle_count = 0;

// 将日期时间字符串转换为分钟数，并计算与当前时间（2025-05-05 13:25）的差值
int convert_to_minutes(const char *time_str, int is_current) {
    int year, month, day, hour, minute;
    if (sscanf(time_str, "%d-%d-%d %d：%d", &year, &month, &day, &hour, &minute) != 5) {
        printf("时间格式错误，请使用 yyyy-MM-dd HH：mm 格式。输入的时间为: %s\n", time_str);
        return -1;
    }
    if (year != 2025) {
        printf("年份必须是2025年。\n");
        return -1;
    }
    int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for (int i = 1; i < month; i++) {
        days += month_days[i];
    }
    days += day - 1;
    int total_minutes = (days * 24 + hour) * 60 + minute;
    if (is_current) {
        days = 0;
        for (int i = 1; i < 5; i++) {
            days += month_days[i];
        }
        days += 5 - 1;
        int current_total = (days * 24 + 13) * 60 + 25;
        return current_total - total_minutes;
    } else {
        return total_minutes;
    }
}

// 隐藏密码输入
void get_password(char *password) {
    int ch;
    int i = 0;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != '\b') {
            password[i++] = (char)ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// 去除字符串末尾的换行符
void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// 打印分隔线
void print_separator() {
    printf("===========================================================\n");
}

// 从文件中读取车辆信息
void read_vehicles_from_file() {
    FILE *file = fopen("vehicles.txt", "r");
    if (file == NULL) {
        perror("无法打开文件 vehicles.txt");
        return;
    }
    char line[256];
    int line_num = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line_num++;
        if (vehicle_count >= MAX_VEHICLES) {
            printf("车辆信息已满，跳过文件中剩余内容。\n");
            break;
        }
        char license_plate[20];
        char owner_name[50];
        int parking_space;
        float balance;
        int user_type;
        char time_str[50];

        if (sscanf(line, "%19s %49s %d %f %d", license_plate, owner_name, &parking_space, &balance, &user_type) != 5) {
            printf("第 %d 行文件格式错误，跳过该行: %s", line_num, line);
            continue;
        }
        remove_newline(license_plate);
        sscanf(line, "%*s %*s %*d %*f %*d %[^\n]", time_str);
        int entry_time = convert_to_minutes(time_str, 0);
        if (entry_time == -1) {
            printf("第 %d 行文件中时间格式错误，跳过该行: %s", line_num, line);
            continue;
        }
        int current_time = convert_to_minutes("2025-05-05 13:25", 0);
        vehicles[vehicle_count].entry_time = current_time - entry_time;
        strcpy(vehicles[vehicle_count].license_plate, license_plate);
        strcpy(vehicles[vehicle_count].owner_name, owner_name);
        vehicles[vehicle_count].parking_space = parking_space;
        vehicles[vehicle_count].balance = balance;
        vehicles[vehicle_count].user_type = user_type;
        vehicle_count++;
    }
    if (ferror(file)) {
        perror("读取文件时发生错误");
    }
    fclose(file);
}

// 新车入库功能
void new_vehicle_entry() {
    if (vehicle_count >= MAX_VEHICLES) {
        printf("停车场已满，无法入库新车。\n");
        return;
    }
    Vehicle new_vehicle;
    char input[MAX_INPUT_LENGTH];

    print_separator();
    printf("新车入库功能\n");
    printf("请输入车牌号: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    strncpy(new_vehicle.license_plate, input, sizeof(new_vehicle.license_plate) - 1);
    new_vehicle.license_plate[sizeof(new_vehicle.license_plate) - 1] = '\0';

    printf("请输入车主姓名: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    strncpy(new_vehicle.owner_name, input, sizeof(new_vehicle.owner_name) - 1);
    new_vehicle.owner_name[sizeof(new_vehicle.owner_name) - 1] = '\0';

    printf("请输入当前时间 (yyyy-MM-dd HH:mm): ");
    char entry_time_str[50];
    fgets(entry_time_str, sizeof(entry_time_str), stdin);
    remove_newline(entry_time_str);
    int entry_time = convert_to_minutes(entry_time_str, 0);
    if (entry_time == -1) {
        printf("时间格式错误，新车入库失败。\n");
        return;
    }
    int current_time = convert_to_minutes("2025-05-05 13:25", 0);
    new_vehicle.entry_time = current_time - entry_time;

    printf("请输入车位号: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    sscanf(input, "%d", &new_vehicle.parking_space);

    int type;
    do {
        printf("请选择用户类型 (0: 访客, 1: 学生, 2: 教师): ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%d", &type) != 1 || type < 0 || type > 2) {
            printf("无效的选择，请重新输入。\n");
        }
    } while (type < 0 || type > 2);

    if (type == 1 || type == 2) {
        char password[20];
        printf("请输入%s密码: ", (type == 1)? "学生" : "教师");
        get_password(password);
        if ((type == 1 && strcmp(password, "student") != 0) || (type == 2 && strcmp(password, "teacher") != 0)) {
            printf("密码错误，新车入库失败。\n");
            return;
        }
    }

    new_vehicle.balance = 0;
    new_vehicle.user_type = type;

    vehicles[vehicle_count++] = new_vehicle;
    printf("新车入库成功。\n");
    print_separator();
}

// 添加车辆信息
void add_vehicle() {
    if (vehicle_count >= MAX_VEHICLES) {
        printf("车辆信息已满，无法添加。\n");
        return;
    }
    Vehicle new_vehicle;
    char input[MAX_INPUT_LENGTH];

    print_separator();
    printf("请输入车牌号: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    strncpy(new_vehicle.license_plate, input, sizeof(new_vehicle.license_plate) - 1);
    new_vehicle.license_plate[sizeof(new_vehicle.license_plate) - 1] = '\0';

    printf("请输入车主姓名: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    strncpy(new_vehicle.owner_name, input, sizeof(new_vehicle.owner_name) - 1);
    new_vehicle.owner_name[sizeof(new_vehicle.owner_name) - 1] = '\0';

    char entry_time_str[50];
    int entry_time;
    do {
        printf("请输入进入时间 (yyyy-MM-dd HH:mm): ");
        fgets(entry_time_str, MAX_INPUT_LENGTH, stdin);
        remove_newline(entry_time_str);
        entry_time = convert_to_minutes(entry_time_str, 0);
    } while (entry_time == -1);
    int current_time = convert_to_minutes("2025-05-05 13:25", 0);
    new_vehicle.entry_time = current_time - entry_time;

    printf("请输入车位号: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    remove_newline(input);
    sscanf(input, "%d", &new_vehicle.parking_space);

    new_vehicle.balance = 0;
    int type;
    do {
        printf("请选择用户类型 (0: 访客, 1: 学生, 2: 教师): ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%d", &type) != 1 || type < 0 || type > 2) {
            printf("无效的选择，请重新输入。\n");
        }
    } while (type < 0 || type > 2);
    new_vehicle.user_type = type;
    vehicles[vehicle_count++] = new_vehicle;
    printf("车辆信息添加成功。\n");
    print_separator();
}

// 显示所有车辆信息
void display_vehicles() {
    if (vehicle_count == 0) {
        print_separator();
        printf("暂无车辆信息。\n");
        print_separator();
        return;
    }
    print_separator();
    printf("| %-10s | %-10s | %-15s | %-8s | %-8s | %-8s |\n",
           "车牌号", "车主姓名", "进入时间", "车位号", "余额", "用户类型");
    print_separator();
    for (int i = 0; i < vehicle_count; i++) {
        const char *user_type_str;
        switch (vehicles[i].user_type) {
            case 0:
                user_type_str = "访客";
                break;
            case 1:
                user_type_str = "学生";
                break;
            case 2:
                user_type_str = "教师";
                break;
            default:
                user_type_str = "未知";
        }
        int total_minutes = vehicles[i].entry_time;
        int days = total_minutes / (24 * 60);
        int remaining_minutes = total_minutes % (24 * 60);
        int hours = remaining_minutes / 60;
        int minutes = remaining_minutes % 60;
        printf("| %-10s | %-10s | %d天 %d小时 %d分钟 | %-8d | %-8.2f | %-8s |\n",
               vehicles[i].license_plate, vehicles[i].owner_name, days, hours, minutes,
               vehicles[i].parking_space, vehicles[i].balance, user_type_str);
    }
    print_separator();
}

// 根据车牌号查找车辆信息
Vehicle *find_vehicle(const char *license_plate) {
    for (int i = 0; i < vehicle_count; i++) {
        if (strcmp(vehicles[i].license_plate, license_plate) == 0) {
            return &vehicles[i];
        }
    }
    return NULL;
}

// 计算费用
float calculate_fee(Vehicle *vehicle, int exit_time) {
    int duration = (exit_time) / 60;
    int max_stay;
    switch (vehicle->user_type) {
        case 0:
            max_stay = VISITOR_MAX_STAY;
            break;
        case 1:
            max_stay = STUDENT_MAX_STAY;
            break;
        case 2:
            max_stay = TEACHER_MAX_STAY;
            break;
        default:
            max_stay = 0;
    }
    float fee = 0;
    if (duration > 1) {
        if (duration <= max_stay) {
            fee = (duration - 1) * HOURLY_RATE;
        } else {
            fee = (max_stay - 1) * HOURLY_RATE + (duration - max_stay) * OVERTIME_RATE;
        }
    }
    if (fee > MAX_FEE) {
        fee = MAX_FEE;
    }
    return fee;
}

// 余额充值页面
void recharge_page(Vehicle *vehicle) {
    char input[MAX_INPUT_LENGTH];
    float amount;
    print_separator();
    printf("余额充值页面\n");
    printf("当前余额: %.2f\n", vehicle->balance);
    printf("请输入充值金额: ");
    while (1) {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%f", &amount) == 1 && amount > 0) {
            break;
        }
        printf("输入无效，请输入一个有效的正数金额: ");
    }
    vehicle->balance += amount;
    printf("充值成功，当前余额: %.2f\n", vehicle->balance);
    print_separator();
}

// 将分钟数转换为日期时间字符串
void minutes_to_time_str(int minutes, char *time_str) {
    int current_time = convert_to_minutes("2025-05-05 13:25", 0);
    int entry_time_minutes = current_time - minutes;
    int year = 2025;
    int month = 1;
    int day = 1;
    int hour = 0;
    int minute = 0;
    int total_minutes = entry_time_minutes;
    int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (total_minutes >= 24 * 60) {
        int days_in_month = month_days[month];
        if (total_minutes >= days_in_month * 24 * 60) {
            total_minutes -= days_in_month * 24 * 60;
            month++;
        } else {
            day += total_minutes / (24 * 60);
            total_minutes %= (24 * 60);
        }
    }
    hour = total_minutes / 60;
    minute = total_minutes % 60;
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d", year, month, day, hour, minute);
}

// 用户菜单
void user_menu(Vehicle *vehicle) {
    int choice;
    char input[MAX_INPUT_LENGTH];
    const char fixed_time[] = "2025-05-05 13:25";
    int exit_time = convert_to_minutes(fixed_time, 0);
    do {
        print_separator();
        printf("用户菜单\n");
        if (vehicle->user_type != 0) {
            printf("1. 余额充值\n");
        }
        printf("2. 出校缴费\n");
        printf("3. 退出\n");
        print_separator();
        printf("请输入你的选择: ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%d", &choice) != 1 || (choice == 1 && vehicle->user_type == 0) || choice < 1 || choice > 3) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (choice) {
            case 1:
                if (vehicle->user_type != 0) {
                    recharge_page(vehicle);
                }
                break;
            case 2: {
                print_separator();
                float fee = calculate_fee(vehicle, vehicle->entry_time);
                float final_fee = fee - vehicle->balance;
                if (final_fee < 0) {
                    final_fee = 0;
                }

                char entry_time_str[20];
                minutes_to_time_str(vehicle->entry_time, entry_time_str);

                int total_minutes = vehicle->entry_time;
                int days = total_minutes / (24 * 60);
                int remaining_minutes = total_minutes % (24 * 60);
                int hours = remaining_minutes / 60;
                int minutes = remaining_minutes % 60;

                printf(ANSI_COLOR_BLUE "入场时间: %s\n" ANSI_COLOR_RESET, entry_time_str);
                printf(ANSI_COLOR_BLUE "停车时长: %d天 %d小时 %d分钟\n" ANSI_COLOR_RESET, days, hours, minutes);

                const char *user_type_str;
                switch (vehicle->user_type) {
                    case 0:
                        user_type_str = "访客";
                        break;
                    case 1:
                        user_type_str = "学生";
                        break;
                    case 2:
                        user_type_str = "教师";
                        break;
                    default:
                        user_type_str = "未知";
                }

                int max_stay;
                switch (vehicle->user_type) {
                    case 0:
                        max_stay = VISITOR_MAX_STAY;
                        break;
                    case 1:
                        max_stay = STUDENT_MAX_STAY;
                        break;
                    case 2:
                        max_stay = TEACHER_MAX_STAY;
                        break;
                    default:
                        max_stay = 0;
                }

                printf(ANSI_COLOR_YELLOW "收费细则:\n" ANSI_COLOR_RESET);
                if (total_minutes / 60 <= 1) {
                    printf("停车未超过1小时，免费。\n");
                } else {
                    int duration = total_minutes / 60;
                    if (duration <= max_stay) {
                        float normal_fee = (duration - 1) * HOURLY_RATE;
                        printf("您是%s，正常停车时长为 %d 小时，每小时收费 %.2f 元。\n", user_type_str, duration, HOURLY_RATE);
                        printf("本次停车费用为 %.2f 元。\n", normal_fee);
                    } else {
                        int normal_hours = max_stay;
                        int overtime_hours = duration - max_stay;
                        float normal_fee = (normal_hours - 1) * HOURLY_RATE;
                        float overtime_fee = overtime_hours * OVERTIME_RATE;
                        printf("您是%s，正常停车时长上限为 %d 小时，每小时收费 %.2f 元；超时部分每小时收费 %.2f 元。\n",
                               user_type_str, normal_hours, HOURLY_RATE, OVERTIME_RATE);
                        printf("正常停车 %d 小时，费用为 %.2f 元；超时 %d 小时，费用为 %.2f 元；总费用为 %.2f 元。\n",
                               normal_hours, normal_fee, overtime_hours, overtime_fee, fee);
                    }
                }

                if (vehicle->user_type != 0 && vehicle->balance >= fee) {
                    vehicle->balance -= fee;
                    printf(ANSI_COLOR_GREEN "缴费成功，扣除余额 %.2f，剩余余额: %.2f\n" ANSI_COLOR_RESET, fee, vehicle->balance);
                } else {
                    vehicle->balance = 0;
                    printf("原需缴纳费用: %.2f\n", fee);
                    printf("使用余额抵扣后，最终应缴纳费用: %.2f\n", final_fee);
                    printf("剩余余额: %.2f\n", vehicle->balance);
                }
                print_separator();
                break;
            }
            case 3:
                printf("退出用户菜单。\n");
                print_separator();
                break;
        }
    } while (choice != 3);
}

// 将停车数据保存到新文件
void save_vehicles_to_file() {
    FILE *file = fopen("new_vehicles.txt", "w");
    if (file == NULL) {
        printf("无法打开文件 new_vehicles.txt 进行写入。\n");
        return;
    }
    for (int i = 0; i < vehicle_count; i++) {
        int current_time = convert_to_minutes("2025-05-05 13:25", 0);
        int entry_time_minutes = current_time - vehicles[i].entry_time;
        int year = 2025;
        int month = 1;
        int day = 1;
        int hour = 0;
        int minute = 0;
        int total_minutes = entry_time_minutes;
        int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while (total_minutes >= 24 * 60) {
            int days_in_month = month_days[month];
            if (total_minutes >= days_in_month * 24 * 60) {
                total_minutes -= days_in_month * 24 * 60;
                month++;
            } else {
                day += total_minutes / (24 * 60);
                total_minutes %= (24 * 60);
            }
        }
        hour = total_minutes / 60;
        minute = total_minutes % 60;
        fprintf(file, "%s %s %d %.2f %d %04d-%02d-%02d %02d:%02d\n",
                vehicles[i].license_plate, vehicles[i].owner_name,
                vehicles[i].parking_space, vehicles[i].balance,
                vehicles[i].user_type, year, month, day, hour, minute);
    }
    fclose(file);
    printf("停车数据已保存到 new_vehicles.txt 文件。\n");
}

// 管理二级菜单
void admin_menu() {
    int choice;
    char input[MAX_INPUT_LENGTH];
    do {
        print_separator();
        printf("管理二级菜单\n");
        printf("1. 显示所有停车数据\n");
        printf("2. 显示超时停车数据\n");
        printf("3. 车辆管理\n");
        printf("4. 保存停车数据到文件\n");
        printf("5. 退出\n");
        print_separator();
        printf("请输入你的选择: ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (choice) {
            case 1:
                display_vehicles();
                break;
            case 2: {
                int found = 0;
                print_separator();
                printf("超时停车数据:\n");
                printf("| %-10s | %-10s | %-15s | %-8s | %-8s |\n",
                       "车牌号", "车主姓名", "进入时间", "车位号", "用户类型");
                print_separator();
                for (int i = 0; i < vehicle_count; i++) {
                    int duration = (vehicles[i].entry_time) / 60;
                    int max_stay;
                    switch (vehicles[i].user_type) {
                        case 0:
                            max_stay = VISITOR_MAX_STAY;
                            break;
                        case 1:
                            max_stay = STUDENT_MAX_STAY;
                            break;
                        case 2:
                            max_stay = TEACHER_MAX_STAY;
                            break;
                        default:
                            max_stay = 0;
                    }
                    if (duration > max_stay) {
                        const char *user_type_str;
                        switch (vehicles[i].user_type) {
                            case 0:
                                user_type_str = "访客";
                                break;
                            case 1:
                                user_type_str = "学生";
                                break;
                            case 2:
                                user_type_str = "教师";
                                break;
                            default:
                                user_type_str = "未知";
                        }
                        int days = vehicles[i].entry_time / (24 * 60);
                        int remaining_minutes = vehicles[i].entry_time % (24 * 60);
                        int hours = remaining_minutes / 60;
                        int minutes = remaining_minutes % 60;
                        printf("| %-10s | %-10s | %d天 %d小时 %d分钟 | %-8d | %-8s |\n",
                               vehicles[i].license_plate, vehicles[i].owner_name, days, hours, minutes,
                               vehicles[i].parking_space, user_type_str);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("暂无超时停车数据。\n");
                }
                print_separator();
                break;
            }
            case 3: {
                int sub_choice;
                do {
                    print_separator();
                    printf("车辆管理子菜单\n");
                    printf("1. 添加车辆信息\n");
                    printf("2. 删除车辆信息\n");
                    printf("3. 退出车辆管理\n");
                    print_separator();
                    printf("请输入你的选择: ");
                    fgets(input, MAX_INPUT_LENGTH, stdin);
                    remove_newline(input);
                    if (sscanf(input, "%d", &sub_choice) != 1 || sub_choice < 1 || sub_choice > 3) {
                        printf("无效的选择，请重新输入。\n");
                        continue;
                    }
                    switch (sub_choice) {
                        case 1:
                            add_vehicle();
                            break;
                        case 2: {
                            char license_plate[20];
                            print_separator();
                            printf("请输入要删除的车牌号: ");
                            fgets(input, MAX_INPUT_LENGTH, stdin);
                            remove_newline(input);
                            strncpy(license_plate, input, sizeof(license_plate) - 1);
                            license_plate[sizeof(license_plate) - 1] = '\0';
                            for (int i = 0; i < vehicle_count; i++) {
                                if (strcmp(vehicles[i].license_plate, license_plate) == 0) {
                                    for (int j = i; j < vehicle_count - 1; j++) {
                                        vehicles[j] = vehicles[j + 1];
                                    }
                                    vehicle_count--;
                                    printf("车辆信息删除成功。\n");
                                    break;
                                }
                            }
                            print_separator();
                            break;
                        }
                        case 3:
                            printf("退出车辆管理。\n");
                            print_separator();
                            break;
                    }
                } while (sub_choice != 3);
                break;
            }
            case 4:
                save_vehicles_to_file();
                break;
            case 5:
                printf("退出管理二级菜单。\n");
                print_separator();
                break;
        }
    } while (choice != 5);
}

// 主菜单
void menu() {
    int choice;
    char input[MAX_INPUT_LENGTH];
    do {
        print_separator();
        printf("校园车辆管理系统 - 登录\n");
        printf("1. 用户登录\n");
        printf("2. 管理员登录\n");
        printf("3. 新车入库\n");
        printf("4. 退出\n");
        print_separator();
        printf("请输入你的选择: ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        remove_newline(input);
        if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (choice) {
            case 1: {
                char license_plate[20];
                print_separator();
                printf("请输入车牌号: ");
                fgets(input, MAX_INPUT_LENGTH, stdin);
                remove_newline(input);
                strncpy(license_plate, input, sizeof(license_plate) - 1);
                license_plate[sizeof(license_plate) - 1] = '\0';
                Vehicle *vehicle = find_vehicle(license_plate);
                if (vehicle) {
                    user_menu(vehicle);
                } else {
                    printf("未找到该车牌号的车辆信息。\n");
                    print_separator();
                }
                break;
            }
            case 2: {
                char admin_password[50];
                print_separator();
                printf("请输入管理员密码: ");
                get_password(admin_password);
                if (strcmp(admin_password, ADMIN_PASSWORD) == 0) {
                    admin_menu();
                } else {
                    printf("密码错误。\n");
                    print_separator();
                }
                break;
            }
            case 3:
                new_vehicle_entry();
                break;
            case 4:
                printf("退出系统。\n");
                print_separator();
                break;
        }
    } while (choice != 4);
}

int main() {
    read_vehicles_from_file();
    menu();
    return 0;
}    

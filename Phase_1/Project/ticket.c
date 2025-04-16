#include "ticket.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/time.h>
#include <stdbool.h>

// 定义 Ticket 和 Order 链表头指针
Ticket *ticket_head = NULL;
Order *order_head = NULL;

// 设置终端为非阻塞模式
void set_conio()
{
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(0, TCSANOW, &new_settings);
}

// 恢复终端到原始模式
void reset_conio()
{
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    stored_settings.c_lflag |= (ICANON | ECHO);
    tcsetattr(0, TCSANOW, &stored_settings);
}

// 检查是否有输入
int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

// 封装输入函数
void input_string(char *str, size_t size, const char *prompt)
{
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
    }
    else
    {
        printf("输入读取失败！\n");
    }
}

void input_int(int *num, const char *prompt)
{
    printf("%s", prompt);
    scanf("%d", num);
    while (getchar() != '\n')
        ;
}

void input_float(float *num, const char *prompt)
{
    printf("%s", prompt);
    scanf("%f", num);
    while (getchar() != '\n')
        ;
}

void welcome()
{
    system("clear");
    set_conio();

    while (1)
    {
        time_t now;
        struct tm *timeinfo;
        time(&now);
        timeinfo = localtime(&now);
        char output[20];

        system("clear");
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*           欢迎使用铁路售票管理系统            *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        strftime(output, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("\n当前时间：%s\r\n", output);

        // 强制刷新输出缓冲区
        fflush(stdout);

        // 增加短暂延迟，确保屏幕刷新完成
        usleep(100 * 1000);

        printf("\n按回车键继续...");

        if (kbhit())
        {
            int c = getchar();
            if (c == '\n')
            {
                break;
            }
        }

        usleep(500 * 1000);
    }

    reset_conio();
}

// 显示主菜单
void showMenu()
{
    usleep(100000);
    system("clear");
    printf("\n=== 铁路售票管理系统 ===\n");
    printf("----------------------------------------\n");
    printf("1. 查看所有票务信息\n");
    printf("2. 购买车票\n");
    printf("3. 退票\n");
    printf("4. 查看个人订单\n");
    printf("5. 管理员功能\n");
    printf("0. 退出系统\n");
    printf("请选择功能 (0-5): ");
}

// 创建新的 Ticket 节点
Ticket *createTicket(const char *line, const char *start, const char *term, const char *start_date, const char *start_time, int min, int num, float price)
{
    Ticket *new_ticket = (Ticket *)malloc(sizeof(Ticket));
    if (new_ticket == NULL)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    strcpy(new_ticket->line, line);
    strcpy(new_ticket->start, start);
    strcpy(new_ticket->term, term);
    strcpy(new_ticket->start_date, start_date);
    strcpy(new_ticket->start_time, start_time);
    new_ticket->min = min;
    new_ticket->num = num;
    new_ticket->price = price;
    new_ticket->next = NULL;
    for (int i = 0; i < MAX_SEATS; i++)
    {
        new_ticket->seat_used[i] = 0;
    }
    return new_ticket;
}

// 创建新的 Order 节点
Order *createOrder(const char *name, const char *id, const char *line, const char *start_date, const char *start_time, int no, float price, const char *seat)
{
    Order *new_order = (Order *)malloc(sizeof(Order));
    if (new_order == NULL)
    {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    strcpy(new_order->name, name);
    strcpy(new_order->id, id);
    strcpy(new_order->line, line);
    strcpy(new_order->start_date, start_date);
    strcpy(new_order->start_time, start_time);
    new_order->no = no;
    new_order->price = price;
    strcpy(new_order->seat, seat);
    new_order->next = NULL;
    return new_order;
}

// 初始化 Ticket 链表
void initTicketList()
{
    FILE *file = fopen("tickets.dat", "rb");
    if (file)
    {
        Ticket temp;
        while (fread(&temp, sizeof(Ticket), 1, file))
        {
            Ticket *new = createTicket(temp.line, temp.start, temp.term, temp.start_date, temp.start_time, temp.min, temp.num, temp.price);
            new->next = ticket_head;
            ticket_head = new;
        }
        fclose(file);
        return;
    }
    ticket_head = createTicket("G101", "北京", "上海", "2025-03-10", "08:00", 300, 100, 553.5);
    Ticket *current = ticket_head;
    current->next = createTicket("G102", "上海", "广州", "2025-03-10", "09:30", 280, 80, 463.0);
    current = current->next;
    current->next = createTicket("G103", "广州", "武汉", "2025-03-10", "07:00", 240, 90, 332.5);
    current = current->next;
    current->next = createTicket("G104", "北京", "广州", "2025-03-11", "10:00", 320, 85, 892.0);
    current = current->next;
    current->next = createTicket("G105", "武汉", "上海", "2025-03-11", "14:30", 180, 95, 426.5);
}

// 比较函数：按车次排序
int compareByLine(const void *a, const void *b)
{
    return strcmp(((Ticket *)a)->line, ((Ticket *)b)->line);
}

// 比较函数：按日期排序
int compareByDate(const void *a, const void *b)
{
    return strcmp(((Ticket *)a)->start_date, ((Ticket *)b)->start_date);
}

// 比较函数：按价格排序
int compareByPrice(const void *a, const void *b)
{
    return ((Ticket *)a)->price - ((Ticket *)b)->price;
}

// 显示所有票务信息
void showAll()
{
    int choice;
    while (1)
    {
        system("clear");
        printf("=== 票务信息显示菜单 ===\n");
        printf("1. 按车次排序显示\n");
        printf("2. 按日期排序显示\n");
        printf("3. 按价格排序显示\n");
        printf("0. 返回主菜单\n");
        printf("请选择功能 (0-3): ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // 清除缓冲区

        if (choice == 0)
        {
            system("clear");
            printf("车次:\t出发站\t到达站\t日期\t\t时间\t历时\t票数\t票价\n");
            Ticket *current = ticket_head;
            while (current)
            {
                printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n",
                       current->line, current->start, current->term, current->start_date, current->start_time, current->min, current->num, current->price);
                current = current->next;
            }
            waitForEnter();
            break;
        }

        system("clear");
        printf("车次:\t出发站\t到达站\t日期\t\t时间\t历时\t票数\t票价\n");

        // 将链表转换为数组以便排序
        int count = 0;
        Ticket *current = ticket_head;
        while (current)
        {
            count++;
            current = current->next;
        }

        Ticket *tickets = (Ticket *)malloc(count * sizeof(Ticket));
        if (tickets == NULL)
        {
            perror("内存分配失败");
            return;
        }

        current = ticket_head;
        for (int i = 0; i < count; i++)
        {
            tickets[i] = *current;
            current = current->next;
        }

        // 根据用户选择进行排序
        switch (choice)
        {
        case 1:
            qsort(tickets, count, sizeof(Ticket), compareByLine);
            break;
        case 2:
            qsort(tickets, count, sizeof(Ticket), compareByDate);
            break;
        case 3:
            qsort(tickets, count, sizeof(Ticket), compareByPrice);
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            free(tickets);
            waitForEnter();
            continue;
        }

        // 显示排序后的票务信息
        for (int i = 0; i < count; i++)
        {
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n",
                   tickets[i].line, tickets[i].start, tickets[i].term, tickets[i].start_date, tickets[i].start_time, tickets[i].min, tickets[i].num, tickets[i].price);
        }

        free(tickets);
        waitForEnter();
    }
}

// 全局变量用于记录当前座位号
int current_seat_number = 1;

// 购买车票
void buyTicket(char *name, char *id)
{
    char date[20];
    char start[20];
    char term[20];
    // Bug 修复：传递数组大小
    input_string(date, sizeof(date), "请输入出发日期 (格式: YYYY-MM-DD): ");
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-')
    {
        printf("日期格式不正确！请按照 YYYY-MM-DD 格式输入。\n");
        return;
    }
    // Bug 修复：传递数组大小
    input_string(start, sizeof(start), "请输入出发站: ");
    // Bug 修复：传递数组大小
    input_string(term, sizeof(term), "请输入到达站: ");

    // 显示符合条件的车票信息
    system("clear");
    printf("车次:\t出发站\t到达站\t日期\t\t时间\t历时\t票数\t票价\n");
    Ticket *current_ticket = ticket_head;
    int found_available = 0;
    while (current_ticket != NULL)
    {
        if (strcmp(current_ticket->start_date, date) == 0 &&
            strcmp(current_ticket->start, start) == 0 &&
            strcmp(current_ticket->term, term) == 0 &&
            current_ticket->num > 0)
        {
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n",
                   current_ticket->line, current_ticket->start, current_ticket->term,
                   current_ticket->start_date, current_ticket->start_time, current_ticket->min,
                   current_ticket->num, current_ticket->price);
            found_available = 1;
        }
        current_ticket = current_ticket->next;
    }

    if (!found_available)
    {
        printf("没有符合条件的车票，请重新选择。\n");
        return;
    }

    char n[20];
    // Bug 修复：传递数组大小
    input_string(n, sizeof(n), "请输入要购买的车次: ");

    current_ticket = ticket_head;
    int found = 0; // 用于标记是否找到对应车次
    while (current_ticket != NULL)
    {
        if (strcmp(current_ticket->line, n) == 0)
        {
            if (current_ticket->num > 0) // 确保还有票
            {
                // 查找可用座位
                int seat_index = -1;
                for (int i = 0; i < MAX_SEATS; i++)
                {
                    if (!current_ticket->seat_used[i])
                    {
                        seat_index = i;
                        current_ticket->seat_used[i] = 1;
                        break;
                    }
                }

                if (seat_index != -1)
                {
                    // 生成座位号，例如 "1车厢3排A座"
                    char seat[20];
                    sprintf(seat, "1车厢%d排A座", seat_index / 10 + 1);

                    printf("购买成功！座位号：%s\n", seat);
                    Order *new_order = createOrder(name, id, current_ticket->line, current_ticket->start_date, current_ticket->start_time, current_seat_number++, current_ticket->price, seat);
                    new_order->next = order_head;
                    order_head = new_order;
                    current_ticket->num--;
                    saveTicketsToFile();
                    saveOrdersToFile();
                }
                else
                {
                    printf("没有可用座位，无法购买！\n");
                }
            }
            else
            {
                printf("票已售罄，无法购买！\n");
            }
            found = 1; // 标记已找到车次
            break;     // 找到后可以退出循环
        }
        current_ticket = current_ticket->next;
    }
    if (!found) // 如果未找到，则输出提示
    {
        printf("输入的车次不存在\n");
    }
}

// 退票
void delOrder(char *name, char *id)
{
    Order *current_order = order_head;
    Order *prev_order = NULL;
    char line[20] = "";
    char seat[20] = "";
    int found = 0; // 标记是否找到订单

    while (current_order != NULL)
    {
        if (strcmp(current_order->id, id) == 0)
        {
            strcpy(line, current_order->line);
            strcpy(seat, current_order->seat); // 获取座位号
            if (prev_order == NULL)
            {
                order_head = current_order->next;
            }
            else
            {
                prev_order->next = current_order->next;
            }
            free(current_order);
            found = 1; // 标记已找到订单
            break;
        }
        prev_order = current_order;
        current_order = current_order->next;
    }

    if (found)
    {
        Ticket *current_ticket = ticket_head;
        while (current_ticket != NULL)
        {
            if (strcmp(line, current_ticket->line) == 0)
            {
                // 解析座位号，找到对应的座位索引
                int seat_index;
                sscanf(seat, "1车厢%d排A座", &seat_index);
                seat_index = (seat_index - 1) * 10;
                current_ticket->seat_used[seat_index] = 0; // 释放座位
                current_ticket->num++;
            }
            current_ticket = current_ticket->next;
        }
        printf("退票成功！\n");
    }
    else
    {
        printf("未找到匹配的订单！\n");
    }
}

void showOrder(char *name, char *id)
{
    Order *p = order_head;
    int found = 0;
    // 先打印表头，使用 %-*s 格式化输出，指定字段宽度
    printf("%-10s%-20s%-10s%-10s%-15s%-15s%-10s\n", "姓名", "身份信息", "车次", "时间", "日期", "座位号", "票价");
    while (p)
    {
        if (strcmp(p->name, name) == 0 && strcmp(p->id, id) == 0)
        {
            // 打印匹配订单的详细信息，使用 %-*s 格式化输出，指定字段宽度
            printf("%-10s%-20s%-10s%-10s%-15s%-15s%-10.2f\n", p->name, p->id, p->line, p->start_time,
                   p->start_date, p->seat, p->price);
            found = 1;
        }
        p = p->next;
    }
    if (!found)
    {
        // 未找到匹配订单时给出提示
        printf("你输入的信息有误，请确认后重新输入\n");
    }
}

// 保存车票信息到文件
void saveTicketsToFile(void)
{
    FILE *file = fopen("tickets.dat", "wb");
    if (file == NULL)
    {
        perror("无法打开 tickets.dat 文件进行写入");
        return;
    }
    Ticket *current = ticket_head;
    while (current)
    {
        if (fwrite(current, sizeof(Ticket), 1, file) != 1)
        {
            perror("写入 tickets.dat 文件时出错");
            break;
        }
        current = current->next;
    }
    fclose(file);
}

// 从文件加载车票信息
void loadTicketsFromFile(void)
{
    FILE *file = fopen("tickets.dat", "rb");
    if (file == NULL)
    {
        perror("无法打开 tickets.dat 文件进行读取");
        return;
    }
    Ticket temp;
    Ticket *prev = NULL;
    while (fread(&temp, sizeof(Ticket), 1, file) == 1)
    {
        Ticket *newTicket = createTicket(temp.line, temp.start, temp.term, temp.start_date, temp.start_time, temp.min, temp.num, temp.price);
        if (prev)
        {
            prev->next = newTicket;
        }
        else
        {
            ticket_head = newTicket;
        }
        prev = newTicket;
    }
    fclose(file);
}

// 保存订单信息到文件
void saveOrdersToFile(void)
{
    FILE *file = fopen("orders.dat", "wb");
    if (file == NULL)
    {
        perror("无法打开 orders.dat 文件进行写入");
        return;
    }
    Order *current = order_head;
    while (current)
    {
        if (fwrite(current, sizeof(Order), 1, file) != 1)
        {
            perror("写入 orders.dat 文件时出错");
            break;
        }
        current = current->next;
    }
    fclose(file);
}

// 从文件加载订单信息
void loadOrdersFromFile(void)
{
    FILE *file = fopen("orders.dat", "rb");
    if (file == NULL)
    {
        perror("无法打开 orders.dat 文件进行读取");
        return;
    }
    Order temp;
    while (fread(&temp, sizeof(Order), 1, file) == 1)
    {
        Order *newOrder = createOrder(temp.name, temp.id, temp.line, temp.start_date, temp.start_time, temp.no, temp.price, temp.seat);
        newOrder->next = order_head;
        order_head = newOrder;
    }
    fclose(file);
}

// 删除记录功能
void deleteRecords()
{
    int del_choice;
    do
    {
        system("clear");
        printf("=== 删除记录子菜单 ===\n");
        printf("1. 按车次删除\n");
        printf("2. 按站点删除\n");
        printf("0. 返回上一级菜单\n");
        input_int(&del_choice, "请选择功能 (0-2): ");

        switch (del_choice)
        {
        case 1:
        {
            char line[STRING];
            // Bug 修复：传递数组大小
            input_string(line, sizeof(line), "请输入要删除的车次：");
            Ticket *current = ticket_head;
            Ticket *prev = NULL;
            while (current)
            {
                if (strcmp(current->line, line) == 0)
                {
                    if (prev == NULL)
                    {
                        ticket_head = current->next;
                    }
                    else
                    {
                        prev->next = current->next;
                    }
                    free(current);
                    saveTicketsToFile();
                    printf("删除成功！\n");
                    waitForEnter();
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (!current)
            {
                printf("未找到该车次，删除失败！\n");
                waitForEnter();
            }
            break;
        }
        case 2:
        {
            char station[STRING];
            // Bug 修复：传递数组大小
            input_string(station, sizeof(station), "请输入要删除的站点：");
            Ticket *current = ticket_head;
            Ticket *prev = NULL;
            while (current)
            {
                if (strcmp(current->start, station) == 0 || strcmp(current->term, station) == 0)
                {
                    if (prev == NULL)
                    {
                        ticket_head = current->next;
                    }
                    else
                    {
                        prev->next = current->next;
                    }
                    Ticket *temp = current;
                    current = current->next;
                    free(temp);
                    saveTicketsToFile();
                    printf("删除包含该站点的车次成功！\n");
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }
            if (!current && !prev)
            {
                printf("未找到包含该站点的车次，删除失败！\n");
                waitForEnter();
            }
            break;
        }
        case 0:
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            waitForEnter();
        }
    } while (del_choice != 0);
}

// 修改记录功能
void modifyRecords()
{
    int mod_choice;
    do
    {
        system("clear");
        printf("=== 修改记录子菜单 ===\n");
        printf("1. 修改列车信息\n");
        printf("2. 修改客户信息\n");
        printf("0. 返回上一级菜单\n");
        input_int(&mod_choice, "请选择功能 (0-2): ");

        switch (mod_choice)
        {
        case 1:
        {
            char line[STRING];
            // Bug 修复：传递数组大小
            input_string(line, sizeof(line), "请输入要修改的车次：");
            Ticket *current = ticket_head;
            while (current)
            {
                if (strcmp(current->line, line) == 0)
                {
                    insertTicket();
                    // 这里简单删除原车次，可根据需求优化
                    Ticket *temp = current;
                    if (current == ticket_head)
                    {
                        ticket_head = current->next;
                    }
                    else
                    {
                        Ticket *prev = ticket_head;
                        while (prev->next != current)
                            prev = prev->next;
                        prev->next = current->next;
                    }
                    free(temp);
                    saveTicketsToFile();
                    printf("修改列车信息成功！\n");
                    showAll();
                    waitForEnter();
                    break;
                }
                current = current->next;
            }
            if (!current)
            {
                printf("未找到该车次，修改失败！\n");
                waitForEnter();
            }
            break;
        }
        case 2:
        {
            char id[STRING];
            // Bug 修复：传递数组大小
            input_string(id, sizeof(id), "请输入要修改的客户身份证号：");
            Order *current = order_head;
            while (current)
            {
                if (strcmp(current->id, id) == 0)
                {
                    char name[STRING];
                    // Bug 修复：传递数组大小
                    input_string(name, sizeof(name), "请输入新的客户姓名：");
                    strcpy(current->name, name);
                    saveOrdersToFile();
                    printf("修改客户信息成功！\n");
                    showOrder(name,id);
                    waitForEnter();
                    break;
                }
                current = current->next;
            }
            if (!current)
            {
                printf("未找到该客户订单，修改失败！\n");
                waitForEnter();
            }
            break;
        }
        case 0:
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            waitForEnter();
        }
    } while (mod_choice != 0);
}

// 查看所有用户信息
void viewAllUserInfo()
{
    Order *current = order_head;
    if (!current)
    {
        printf("目前没有用户订单信息。\n");
        return;
    }

    // 打印表头，调整字段宽度
    printf("%-10s%-20s%-15s%-10s%-15s%-15s%-10s\n", "姓名", "身份信息", "车次", "时间", "日期", "座位号", "票价");

    // 遍历订单链表并打印信息，调整字段宽度
    while (current)
    {
        printf("%-10s%-20s%-15s%-10s%-15s%-15s%-10.2f\n",
               current->name, current->id, current->line,
               current->start_time, current->start_date,
               current->seat, current->price);
        current = current->next;
    }
    waitForEnter();
}

// 管理员功能函数
void adminFunctions()
{
    system("clear");
    char password[20];
    // Bug 修复：传入数组大小
    input_string(password, sizeof(password), "请输入管理员密码：");

    if (strcmp(password, "admin123") == 0)
    {
        int choice;
        do
        {
            system("clear");
            printf("=== 管理员功能菜单 ===\n");
            printf("1. 查看所有用户信息\n");
            printf("2. 添加车次\n");
            printf("3. 删除记录\n");
            printf("4. 修改记录\n");
            printf("0. 返回主菜单\n");
            input_int(&choice, "请选择功能 (0-4): ");

            switch (choice)
            {
            case 1:
            {
                viewAllUserInfo();
                break;
            }
            case 2:
                insertTicket();
                saveTicketsToFile(); // 保存新的车票信息到文件
                waitForEnter();
                break;
            case 3:
                deleteRecords();
                break;
            case 4:
                modifyRecords();
                break;
            case 0:
                break;
            default:
                printf("无效的选择，请重新输入。\n");
                waitForEnter();
            }
        } while (choice != 0);
    }
    else
    {
        printf("密码错误！");
        waitForEnter();
    }
}
// 封装输入姓名和身份证号的函数
void inputNameAndId(char *name, char *id)
{
    // Bug 修复：传递数组的实际大小
    input_string(name, STRING, "请输入姓名: ");
    while (1)
    {
        // Bug 修复：传递数组的实际大小
        input_string(id, STRING, "请输入身份证号: ");
        if (strlen(id) == 18)
        {
            break;
        }
        else
        {
            printf("身份证号码必须为18位，请重新输入。\n");
        }
    }
}

// 封装等待用户按回车键的函数
void waitForEnter()
{
    printf("按回车键返回菜单...");
    while (getchar() != '\n')
        ;
}

void insertTicket()
{
    char line[STRING];
    char start[STRING];
    char term[STRING];
    char start_date[STRING];
    char start_time[STRING];
    int min;
    int num;
    float price;

    // Bug 修复：传递数组大小
    input_string(line, sizeof(line), "请输入车次：");
    // Bug 修复：传递数组大小
    input_string(start, sizeof(start), "请输入出发站：");
    // Bug 修复：传递数组大小
    input_string(term, sizeof(term), "请输入到达站：");
    // Bug 修复：传递数组大小
    input_string(start_date, sizeof(start_date), "请输入日期：");
    // Bug 修复：传递数组大小
    input_string(start_time, sizeof(start_time), "请输入时间：");
    input_int(&min, "请输入历时：");
    input_int(&num, "请输入票数：");
    input_float(&price, "请输入票价：");

    // 显示子菜单
    int choice;
    while (1)
    {
        system("clear");
        printf("=== 插入方式选择菜单 ===\n");
        printf("1. 头插法插入车次\n");
        printf("2. 尾插法插入车次\n");
        printf("请选择插入方式 (1-2): ");
        input_int(&choice, "请输入有效的选择: ");

        if (choice == 1 || choice == 2)
        {
            break;
        }
        else
        {
            printf("无效的选择，请重新输入。\n");
            waitForEnter();
        }
    }

    Ticket *ticket = createTicket(line, start, term, start_date, start_time, min, num, price);

    if (choice == 1)
    {
        // 头插法
        ticket->next = ticket_head;
        ticket_head = ticket;
        showAll();
    }
    else
    {
        // 尾插法
        if (ticket_head == NULL)
        {
            ticket_head = ticket;
        }
        else
        {
            Ticket *current = ticket_head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = ticket;
            ticket->next = NULL;
        }
        showAll();
    }
}
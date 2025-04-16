#ifndef TICKET_H
#define TICKET_H

#define MAX_SEATS 100
#define STRING 20

typedef struct Ticket {
    char line[STRING];
    char start[STRING];
    char term[STRING];
    char start_date[STRING];
    char start_time[STRING];
    int min;
    int num;
    float price;
    int seat_used[MAX_SEATS];
    struct Ticket *next;
} Ticket;

typedef struct Order {
    char name[STRING];
    char id[STRING];
    char line[STRING];
    char start_date[STRING];
    char start_time[STRING];
    int no;
    float price;
    char seat[STRING];
    struct Order *next;
} Order;

// 函数声明
void set_conio();
void reset_conio();
int kbhit();
void welcome();
void showMenu();
Ticket *createTicket(const char*, const char*, const char*, const char*, const char*, int, int, float);
Order *createOrder(const char*, const char*, const char*, const char*, const char*, int, float, const char*);
void initTicketList();
void showAll();
void buyTicket(char*,char *);
void delOrder(char*,char *);
void showOrder(char*,char *);
void saveTicketsToFile();
void loadTicketsFromFile();
void saveOrdersToFile();
void loadOrdersFromFile();
void adminFunctions();
void inputNameAndId(char*,char *);
void waitForEnter();
void insertTicket();

#endif

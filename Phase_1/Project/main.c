#include "ticket.h"
#include <stdio.h>

int main()
{
    int choice;
    char date[50];
    char name[50];
    char id[20];

    initTicketList();
    loadOrdersFromFile();
    welcome();

    while (1)
    {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 0:
            printf("\n感谢您的使用，再见！\n");
            fflush(stdout);
            saveTicketsToFile();
            saveOrdersToFile();
            return 0;
        case 1:
            showAll(NULL);
            waitForEnter();
            break;
            break;
        case 2:
            showAll(NULL);
            inputNameAndId(name, id);
            buyTicket(name, id);
            waitForEnter();
            break;
        case 3:
            inputNameAndId(name, id);
            showOrder(name, id);
            delOrder(name, id);
            waitForEnter();
            break;
        case 4:
            inputNameAndId(name, id);
            showOrder(name, id);
            waitForEnter();
            break;
        case 5:
            adminFunctions();
            waitForEnter();
            break;
        default:
            printf("无效的选择，请输入 0 - 6 之间的数字。\n");
            waitForEnter();
            break;
        }
    }
    return 0;
}
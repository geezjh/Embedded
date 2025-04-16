#include <stdio.h>
#include "slist.h"

int main()
{
    BusRoute routes[] = {
        {"1路", "火车站", "汽车站", 10.5},
        {"2路", "机场", "市中心", 25.0},
        {"3路", "公园", "商场", 5.2}};
    int size = sizeof(routes) / sizeof(routes[0]);
    BusRoute *head = slist_insert(routes, size);
    slist_showall(head);
    slist_destory(&head);
    slist_save(head, "bus.dat");
    BusRoute *read = slist_read("bus.dat");
    printf("原始链表数据：\n");
    slist_showall(read);
    read = slist_remove(read);
    printf("\n删除里程最短节点后的链表数据：\n");
    slist_showall(read);
    slist_save(read,"bus.dat");
    slist_destory(&read);
    slist_destory(&head);
    return 0;
}

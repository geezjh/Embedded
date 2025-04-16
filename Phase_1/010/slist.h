// 定义一个表示公交线路的结构体，要求有线路名称，起始站，终点站，里程等成员，
// 定义结构体数组，将结构体数组中的数据插入到一个单向链表中，并输出；
#ifndef __SLIST_H
#define __SLIST_H

typedef struct BusRoute
{
   char name[20];
   char start[20];
   char end[20];
   float mileage;
   struct BusRoute *next;
} BusRoute;
BusRoute *slist_insert(BusRoute *, int);
void slist_showall(BusRoute *);
void slist_destory(BusRoute **);
void slist_save(BusRoute *, const char *);
BusRoute *slist_read(const char *);
BusRoute *slist_remove(BusRoute *);
#endif

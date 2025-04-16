#ifndef __SLIST_H
#define __SLIST_H

typedef struct
{
   int line;
   char start[20];
   char term[20];
   float kilo;
} data_t;

typedef struct node
{
   data_t data;
   struct node *next;
} node_t;

int slist_create(node_t **, data_t);

int slist_addhead(node_t **, data_t);
int slist_addtail(node_t **, data_t);
int slist_insert(node_t **, data_t, data_t);

int slist_delete(node_t **, data_t);
node_t *slist_query(node_t *, data_t);
int slist_update(node_t *, data_t, data_t);

void slist_destroy(node_t **);
int slist_showall(node_t *);
int del_line(node_t **, data_t);
int del_start(node_t **, data_t);
#endif

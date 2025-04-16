#ifndef __LSTACK_H
#define __LSTACK_H

typedef int data_t;
typedef struct node
{
   data_t data;
   struct node *next;
} node_t;
typedef struct
{
   node_t *head;
   long size;
   long top;
} lstack_t;

int lstack_create(lstack_t *, long);

int lstack_isfull(const lstack_t *);
int lstack_isempty(const lstack_t *);

int lstack_push(lstack_t *, data_t);
int lstack_pop(lstack_t *, data_t *);

void lstack_free(lstack_t *);
#endif

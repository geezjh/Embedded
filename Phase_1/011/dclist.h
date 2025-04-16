#ifndef __DCLIST_H
#define __DCLIST_H

typedef int data_t;

typedef struct node
{
   data_t data;
   struct node *prev;
   struct node *next;
} node_t;

int dclist_create(node_t **, data_t);

int dclist_insert(node_t **, data_t);
int dclist_H_insert(node_t **, data_t);

int dclist_delete(node_t **, data_t);
node_t *dclist_query(node_t *, data_t);
int dclist_update(node_t *, data_t, data_t);
int dclist_ring(data_t, data_t);
void dclist_destroy(node_t **);
int dclist_showall(node_t *);

#endif

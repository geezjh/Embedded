#ifndef __BST_H
#define __BST_H

typedef int data_t;

typedef struct node
{
   data_t data;
   struct node *left;
   struct node *right;
} node_t;

int bst_create(node_t **, data_t);

int bst_insert(node_t **, data_t);

void bst_preorder(node_t *root);
void bst_midorder(node_t *root);
void bst_postorder(node_t *root);

int bst_delete(node_t **, data_t);
int bst_update(node_t **, data_t, data_t);

int bst_query(node_t *, data_t);
void bst_destroy(node_t **);
#endif

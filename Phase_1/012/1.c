#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int insert(node_t **root, data_t data)
{
    node_t *pnew = (node_t *)malloc(sizeof(node_t));
    if (pnew == NULL)
    {
        return -1;
    }
    pnew->data = data;
    pnew->right = pnew->left = NULL;
    if (*root == NULL)
    {
        *root = pnew;
        return 0;
    }
    node_t *p = *root, *q = NULL;
    while (p)
    {
        q = p;
        if (memcmp(&data, &p->data, sizeof(data_t)) < 0)
            p = p->left;
        else
            p = p->right;
    }
    if (memcmp(&data, &p->data, sizeof(data_t)) < 0)
        q->left = pnew;
    else
        q->right = pnew;
    return 0;
}
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bst_create(node_t **root, data_t data)
{
     node_t *p = (node_t *)malloc(sizeof(node_t));
     if (p == NULL)
          return -1;

     p->data = data;
     p->left = p->right = NULL;

     *root = p;
     return 0;
}

int bst_insert(node_t **root, data_t data)
{
     node_t *pnew = (node_t *)malloc(sizeof(node_t));
     if (pnew == NULL)
          return -1;

     pnew->data = data;
     pnew->left = pnew->right = NULL;

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
     if (memcmp(&data, &q->data, sizeof(data_t)) < 0)
          q->left = pnew;
     else
          q->right = pnew;
     return 0;
}

void bst_preorder(node_t *root)
{
     if (root == NULL)
          return;

     printf("%5d", root->data);
     bst_preorder(root->left);
     bst_preorder(root->right);
}

void bst_midorder(node_t *root)
{
     if (root == NULL)
          return;

     bst_midorder(root->left);
     printf("%5d", root->data);
     bst_midorder(root->right);
}

void bst_postorder(node_t *root)
{
     if (root == NULL)
          return;

     bst_postorder(root->left);
     bst_postorder(root->right);
     printf("%5d", root->data);
}

int bst_query(node_t *root, data_t data)
{
     node_t *p = root;
     while (p)
     {
          if (memcmp(&data, &p->data, sizeof(data_t)) < 0)
               p = p->left;
          else if (memcmp(&data, &p->data, sizeof(data_t)) > 0)
               p = p->right;
          else
               return 0;
     }
     return -1;
}
int bst_delete(node_t **root, data_t delete)
{
     node_t *del = *root;    // 指向待删除的节点
     node_t *replace = NULL; // 指向实际被删除的节点
     node_t *parent = NULL;  // 指向实际被删除的节点的双亲节点

     while (del)
     {
          if (memcmp(&delete, &del->data, sizeof(data_t)) < 0) // 待删除节点数据<当前节点,向左子数查找
          {
               parent = del;
               del = del->left;
          }
          else if (memcmp(&delete, &del->data, sizeof(data_t)) > 0) ////待删除节点数据<当前节点,向左子数查找
          {
               parent = del;
               del = del->right;
          }
          else // 找到待删除的节点
          {
               if (del->left) // 待删除的节点有左子数
               {
                    parent = del;
                    replace = del->left;
                    while (replace->right) // 找出左子数中的最大节点,此节点也是实际被删除的节点
                    {
                         parent = replace;
                         replace = replace->right;
                    }
                    del->data = replace->data;   // 用实际删除节点的数据替换待删除节点数据
                    if (parent->left == replace) // 如果左子数中最大节点位于双亲节点的左子数
                         parent->left = replace->left;
                    else
                         parent->right = replace->left;
                    free(replace);
               }
               else if (del->right) // 待删除的节点仅有右子数
               {
                    parent = del;
                    replace = del->right;
                    while (replace->left) // 找出右子数中的最小节点,此节点也是实际被删除的节点
                    {
                         parent = replace;
                         replace = replace->left;
                    }
                    del->data = replace->data;   // 用实际删除节点的数据替换待删除节点数据
                    if (parent->left == replace) // 如果左子数中最大节点位于双亲节点的左子数
                         parent->left = replace->right;
                    else
                         parent->right = replace->right;
                    free(replace);
               }
               else // 待删除的节点是叶子
               {
                    if (parent == NULL)
                    {
                         free(del);
                         *root = NULL;
                         return 0;
                    }
                    if (parent->left == del)
                         parent->left = NULL;
                    else
                         parent->right = NULL;

                    free(del);
               }
          }
     }

     return 0;
}
int bst_update(node_t **root, data_t old, data_t new)
{
     if (bst_query(*root, old) == -1)
     {
          return -1; // 旧节点不存在，直接返回错误
     }
     bst_delete(root, old);
     bst_insert(root, new);
     return 0;
}

static void bst_free(node_t *root)
{
     if (root == NULL)
          return;
     bst_free(root->left);
     bst_free(root->right);
     free(root);
}

void bst_destroy(node_t **root)
{
     bst_free(*root);
     *root = NULL;
}

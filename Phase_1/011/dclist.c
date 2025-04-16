#include "dclist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int dclist_create(node_t **head, data_t data)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
        return -1;

    p->data = data;
    p->prev = p->next = p;

    *head = p;
    return 0;
}
static void _dclist_insert(node_t *new, node_t *prev, node_t *next)
{
    new->prev = prev;
    new->next = next;

    prev->next = new;
    next->prev = new;
}
int dclist_insert(node_t **head, data_t data)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
        return -1;

    p->data = data;
    p->prev = p->next = p;

    if (*head == NULL)
    {
        *head = p;
        return 0;
    }
    _dclist_insert(p, (*head)->prev, *head);
    return 0;
}

int dclist_H_insert(node_t **head, data_t data)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
        return -1;

    p->data = data;
    p->prev = p->next = p;

    if (*head == NULL)
    {
        *head = p;
        return 0;
    }

    _dclist_insert(p, (*head)->prev, *head);
    *head = p;
    return 0;
}
static void _dclist_remove(node_t *del, node_t *prev, node_t *next)
{
    prev->next = next;
    next->prev = prev;
    free(del);
}
int dclist_delete(node_t **head, data_t data)
{
    node_t *del = dclist_query(*head, data);
    if (del == NULL)
        return -1;

    node_t *p = *head;
    if (del == p) // 删除的是头节点
    {
        if (p->next == p) // 唯一一个节点
        {
            *head = NULL;
            free(p);
            return 0;
        }
        _dclist_remove(del, del->prev, del->next);
        *head = p->next;
        return 0;
    }
    _dclist_remove(del, del->prev, del->next);
    return 0;
}
node_t *dclist_query(node_t *head, data_t data)
{
    node_t *p = head;

    while (p)
    {
        if (memcmp(&p->data, &data, sizeof(data_t)) == 0)
            return p;
        p = p->next;
        if (p == head)
            break;
    }
    return NULL;
}
int dclist_update(node_t *head, data_t old, data_t new)
{
    node_t *p = dclist_query(head, old);
    if (p == NULL)
        return -1;
    p->data = new;
    return 0;
}

void dclist_destroy(node_t **head)
{
    if (*head == NULL)
        return;
    (*head)->prev->next = NULL;
    node_t *p = *head, *q = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *head = NULL;
}
int dclist_showall(node_t *head)
{
    node_t *p = head;

    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
        if (p == head)
            break;
    }
    printf("\n");
    return 0;
}

int dclist_ring(data_t n, data_t num)
{
    node_t *head = NULL;
    for (int i = 1; i <= n; i++)
    {
        dclist_insert(&head, i);
    }
    node_t *p = head, *q = NULL;
    while (p->next != p)
    {
        for (int i = 1; i < num; i++)
        {
            q = p;
            p = p->next;
        }
        node_t *temp = p;
        if (q)
        {
            q->next = p->next;
            p->next->prev = q;
        }
        else
        {
            head = p->next;
            p->next->prev = p->prev;
            p->prev->next = p->next;
        }
        p = p->next;
        free(temp);
    }
    int last = p->data;
    free(p);
    return last;
}
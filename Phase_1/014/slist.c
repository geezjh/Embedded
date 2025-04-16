#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int slist_create(node_t **head, data_t data)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
        return -1;

    p->data = data;
    p->next = NULL;

    *head = p;
    return 0;
}

int slist_addhead(node_t **head, data_t data)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    if (p == NULL)
        return -1;

    p->data = data;
    p->next = *head;
    *head = p;
    return 0;
}
int slist_addtail(node_t **head, data_t data)
{
    node_t *pnew = (node_t *)malloc(sizeof(node_t));
    if (pnew == NULL)
        return -1;

    pnew->data = data;
    pnew->next = NULL;

    node_t *p = *head, *q = NULL;
    while (p)
    {
        q = p;
        p = p->next;
    }
    if (q)
        q->next = pnew;
    else
        *head = pnew;
    return 0;
}

int slist_insert(node_t **head, data_t pos, data_t new)
{
    node_t *pnew = (node_t *)malloc(sizeof(node_t));
    if (pnew == NULL)
        return -1;

    pnew->data = new;
    pnew->next = NULL;

    if (*head == NULL)
    {
        *head = pnew;
        return 0;
    }
    node_t *p = *head, *q = NULL;
    if (memcmp(&p->data, &pos, sizeof(data_t)) == 0)
    {
        pnew->next = p;
        *head = pnew;
        return 0;
    }
    while (p)
    {
        if (memcmp(&p->data, &pos, sizeof(data_t)) == 0)
        {
            pnew->next = p;
            q->next = pnew;
            return 0;
        }
        q = p;
        p = p->next;
    }
    q->next = pnew;
    return 0;
}

int slist_delete(node_t **head, data_t delete)
{
    if (*head == NULL)
        return -1;

    node_t *p = *head, *q = NULL;
    if (memcmp(&p->data, &delete, sizeof(data_t)) == 0)
    {
        *head = p->next;
        free(p);
        return 0;
    }
    while (p)
    {
        if (memcmp(&p->data, &delete, sizeof(data_t)) == 0)
        {
            q->next = p->next;
            free(p);
            return 0;
        }
        q = p;
        p = p->next;
    }
    return -1;
}

node_t *slist_query(node_t *head, data_t tbfind)
{
    node_t *p = head;
    while (p)
    {
        if (memcmp(&p->data, &tbfind, sizeof(data_t)) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int slist_update(node_t *head, data_t old, data_t new)
{
    node_t *p = slist_query(head, old);
    if (p == NULL)
        return -1;
    p->data = new;
    return 0;
}

void slist_destroy(node_t **head)
{
    node_t *p = *head, *q = NULL;

    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *head = NULL;
}

int slist_showall(node_t *head)
{
    node_t *p = head;
    printf("%-12s%-12s%-12s%-12s\n", "车次", "起始站", "终点站", "里程");
    while (p)
    {
        printf("%-12d%-12s%-12s%-7.1f\n", p->data.line, p->data.start, p->data.term, p->data.kilo);
        p = p->next;
    }
    return 0;
}
int del_line(node_t **head, data_t delete)
{

    if (*head == NULL)
        return -1;

    node_t *p = *head, *q = NULL;
    if (p->data.line == delete.line)
    {
        *head = p->next; // 更新头指针
        free(p);
        p = *head;
    }
    while (p)
    {
        if (p->data.line == delete.line)
        {
            q->next = p->next;
            free(p);
            p = q->next;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    printf("删除后:\n");
    slist_showall(*head);
    return 0;
}

int del_start(node_t **head, data_t delete)
{
    if (*head == NULL)
        return -1;

    node_t *p = *head, *q = NULL;
    if (strcmp(p->data.start, delete.start) == 0) // 使用 strcmp 比较字符数组
    {
        *head = p->next; // 更新头指针
        free(p);
        p = *head;
    }
    while (p)
    {
        if (strcmp(p->data.start, delete.start) == 0) // 使用 strcmp 比较字符数组
        {
            q->next = p->next;
            free(p);
            p = q->next;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }
    printf("删除后:\n");
    slist_showall(*head);
    return 0;
}

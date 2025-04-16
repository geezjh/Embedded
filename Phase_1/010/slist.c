#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BusRoute *slist_insert(BusRoute *arr, int size)
{
    BusRoute *head = NULL;
    BusRoute *tail = NULL;
    BusRoute *p = arr;
    for (int i = 0; i < size; i++)
    {
        BusRoute *pnew = (BusRoute *)malloc(sizeof(BusRoute));
        if (pnew == NULL)
        {
            printf("地址分配失败\n");
            return NULL;
        }

        strcpy(pnew->name, p->name);
        strcpy(pnew->start, p->start);
        strcpy(pnew->end, p->end);
        pnew->mileage = p->mileage;
        p++;
        pnew->next = NULL;

        if (head == NULL)
        {
            head = pnew;
            tail = pnew;
        }
        else
        {
            tail->next = pnew;
            tail = pnew;
        }
    }

    return head;
}

void slist_showall(BusRoute *head)
{
    BusRoute *p = head;
    while (p)
    {
        printf("%s ", p->name);
        printf("%s ", p->start);
        printf("%s ", p->end);
        printf("%.2f\n", p->mileage);
        p = p->next;
    }
}

void slist_destory(BusRoute **head)
{
    BusRoute *p = *head, *q = NULL;

    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *head = NULL;
}

void slist_save(BusRoute *head, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("file open failed\n");
        return;
    }

    BusRoute *p = head;
    while (p)
    {
        fwrite(p->name, sizeof(char), sizeof(p->name), fp);
        fwrite(p->start, sizeof(char), sizeof(p->start), fp);
        fwrite(p->end, sizeof(char), sizeof(p->end), fp);
        fwrite(&p->mileage, sizeof(float), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

BusRoute *slist_read(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("无法打开文件 %s\n", filename);
        return NULL;
    }

    BusRoute *head = NULL;
    BusRoute *tail = NULL;
    BusRoute temp;

    while (fread(&temp, sizeof(BusRoute), 1, file) == 1)
    {
        BusRoute *newNode = (BusRoute *)malloc(sizeof(BusRoute));
        if (newNode == NULL)
        {
            printf("内存分配失败\n");
            fclose(file);
            return NULL;
        }
        memcpy(newNode, &temp, sizeof(BusRoute));
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(file);
    return head;
}

// 找出里程最短的节点并删除
BusRoute *slist_remove(BusRoute *head)
{
    if (head == NULL || head->next == NULL)
    {
        if (head != NULL)
        {
            free(head);
        }
        return NULL;
    }

    BusRoute *prevShortest = NULL;
    BusRoute *shortest = head;
    BusRoute *prev = NULL;
    BusRoute *current = head;

    while (current != NULL)
    {
        if (current->mileage < shortest->mileage)
        {
            shortest = current;
            prevShortest = prev;
        }
        prev = current;
        current = current->next;
    }

    if (prevShortest == NULL)
    {
        head = shortest->next;
    }
    else
    {
        prevShortest->next = shortest->next;
    }

    free(shortest);
    return head;
}
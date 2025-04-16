#include "function.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int addrecord(node_t **head, int select)
{

    data_t data;

    printf("请输入线路号:");
    scanf("%d", &data.line);

    printf("请输入起始站:");
    scanf("%s", data.start);

    printf("请输入终点站:");
    scanf("%s", data.term);

    printf("请输入里程:");
    scanf("%f", &data.kilo);

    int ret = 0;
    if (select == 1)
        ret = slist_addhead(head, data);
    else
        ret = slist_addtail(head, data);

    return ret;
}

static bool compare(node_t *p, node_t *q, int select)
{
    switch (select)
    {
    case 1:
        return p->data.line < q->data.line;
    case 2:
        return strcmp(p->data.start, q->data.start) < 0;
    case 3:
        return p->data.kilo < q->data.kilo;
    }
    return false;
}

void Sort(node_t *head, int select)
{
    node_t *p = head;
    int n = 0;

    while (p)
    {
        n++;
        p = p->next;
    }
    node_t **arr = (node_t **)calloc(sizeof(node_t *), n);
    if (arr == NULL)
        return;

    p = head;
    int k = 0;
    while (p)
    {
        arr[k++] = p;
        p = p->next;
    }

    register int i = 0, j = 0;

    for (i = 0; i < n - 1; i++)
    {
        int min = i;
        for (j = i + 1; j < n; j++)
        {
            if (compare(arr[j], arr[min], select))
                min = j;
        }
        if (min != i)
        {
            node_t *t = arr[min];
            arr[min] = arr[i];
            arr[i] = t;
        }
    }

    printf("%-12s%-12s%-12s%-12s\n", "车次", "起始站", "终点站", "里程");
    for (int i = 0; i < n; i++)
    {
        printf("%-12d%-12s%-12s%-7.1f\n", arr[i]->data.line, arr[i]->data.start, arr[i]->data.term, arr[i]->data.kilo);
    }

    free(arr);
}

int delrecord(node_t **head, int select)
{
    printf("原始数据：\n");
    slist_showall(*head);
    data_t data;

    int ret = -1;
    if (select == 1)
    {
        printf("请输入线路号:");
        scanf("%d", &data.line);
        ret = del_line(head, data);
    }

    else
    {
        printf("请输入起始站:");
        scanf("%s", data.start);
        ret = del_start(head, data);
    }

    return ret;
}

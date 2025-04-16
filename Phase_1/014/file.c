#include "file.h"
#include <stdio.h>

int load(node_t **head, const char *file)
{
    FILE *fp = fopen(file, "rb");
    if (fp == NULL)
        return -1;

    data_t data;
    while (1 == fread(&data, sizeof(data_t), 1, fp))
        slist_addtail(head, data);

    fclose(fp);
    return 0;
}
int save(node_t *head, const char *file)
{
    FILE *fp = fopen(file, "wb");
    if (fp == NULL)
        return -1;

    node_t *p = head;
    while (p)
    {
        fwrite(&p->data, sizeof(data_t), 1, fp);
        p = p->next;
    }
    fclose(fp);
    return 0;
}

#include <stdio.h>
#include "dclist.h"

int main(int argc, char **argv)
{
    int n, num;
    printf("请输入小朋友数量和报号数字：\n");
    scanf("%d%d", &n, &num);
    printf("最后一个出列的小朋友编号是: %d\n", dclist_ring(n, num));
    node_t *head = NULL;
    for (int i = 1; i <= n; i++)
    {
        dclist_H_insert(&head, i);
    }
    dclist_showall(head);
    dclist_destroy(&head);
    return 0;
}

#include "bst.h"
#include <stdio.h>

#define QUERY 0

int main(int argc, char **argv)
{
    int a[] = {6, 2, 8, 4, 9, 5, 7, 1, 3};
    int n = sizeof a / sizeof a[0];

    node_t *root = NULL;

    for (register int i = 0; i < n; i++)
        bst_insert(&root, a[i]);

    puts("======前序遍历=======");
    bst_preorder(root);
    printf("\n================\n");

    puts("======中序遍历=======");
    bst_midorder(root);
    printf("\n================\n");

    puts("======后序遍历=======");
    bst_postorder(root);
    printf("\n================\n");
#if (QUERY == 1)
    while (1)
    {
        printf("请输入要查询的数据(-1退出):");
        data_t data;
        scanf("%d", &data);
        if (data == -1)
            break;

        if (-1 == bst_query(root, data))
        {
            fprintf(stderr, "查询失败!请重试...\n");
            continue;
        }
        puts("======中序遍历=======");
        bst_midorder(root);
        printf("\n================\n");
    }
#elif (QUERY == 2)
    while (1)
    {
        printf("请输入要删除的数据(-1退出):");
        data_t data;
        scanf("%d", &data);
        if (data == -1)
            break;

        if (-1 == bst_delete(&root, data))
        {
            fprintf(stderr, "删除失败!请重试...\n");
            continue;
        }
        puts("======中序遍历=======");
        bst_midorder(root);
        printf("\n================\n");
    }
#else
    printf("请输入要更新的数据：\n");
    data_t x, y;
    scanf("%d%d", &x, &y);
    if (-1 == bst_update(&root, x, y))
        fprintf(stderr, "删除失败!请重试...\n");
    puts("======中序遍历=======");
    bst_midorder(root);
    printf("\n================\n");

#endif

    bst_destroy(&root);
    return 0;
}

#include <stdio.h>

void my_enter(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}

int main()
{
    int a[5];
    int *p = a;
    printf("请输入5个数: ");
    my_enter(p, 5);
    printf("反向输出的数组: ");
    for (int i = 4; i >= 0; i--)
    {
        printf("%d ", *(p + i));  // 使用指针反向输出数组
    }
    printf("\n");
    return 0;
}

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
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i % 2 != 0)
        {
            sum += *(p + i);
        }
    }
    printf("奇数索引位置的数组元素之和为：%d\n", sum);
    return 0;
}

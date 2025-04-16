#include <stdio.h>

void my_enter(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);  
    }
}

void SortArray(int a[], int n)
{
    // 冒泡排序实现
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                // 交换 a[j] 和 a[j + 1]
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int a[5];
    printf("请输入5个数: ");
    my_enter(a, 5);
    SortArray(a, 5);
    printf("排序后的数组: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

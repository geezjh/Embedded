#include <stdio.h>

void my_enter(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}

void swap(int a[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

int main()
{
    int a[5];
    printf("请输入5个数: ");
    my_enter(a, 5);
    swap(a, 5);
    printf("首尾互换后的数组: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

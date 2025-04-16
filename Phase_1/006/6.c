#include <stdio.h>

float ave(int x, int k)
{
    return (float)x / k;
}

int main()
{
    int num[100];
    int sum = 0;
    int k = 0;
    printf("请输入数据：以0结束");
    for (int i = 0; i < 100; i++)
    {
        scanf("%d", &num[i]); // 使用&num[i]传递变量地址
        if (num[i] == 0)
        {
            k = i;
            break;
        }
        sum += num[i];
    }
    if (k == 0)
    { // 检查k是否为0，避免除以0的错误
        printf("没有输入有效的数据。\n");
    }
    else
    {
        float res = ave(sum, k);
        printf("你输入了%d个数,平均数为：%.2f\n", k, res); // 添加换行符以提高可读性
    }

    return 0;
}

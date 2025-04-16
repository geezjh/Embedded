#include <stdio.h>

int main()
{
    int stations, fare;
    float moneyPaid, change;
    int bills[6] = {100, 50, 20, 10, 5, 1}; // 可识别的钞票面额
    int count[6] = {0};                     // 每种面额的钞票张数
    printf("请输入站数：");                  // 输入站数
    scanf("%d", &stations);
    if (stations <= 6)
    {
        fare = 2;
    }
    else if (stations <= 10)
    {
        fare = 3;
    }
    else
    {
        fare = 4;
    }
    printf("请输入钱数：(可识别面额：100,50,20,10,5,1)");
    scanf("%f", &moneyPaid);
    change = moneyPaid - fare;                              
    if (change < 0)
    {
        printf("支付金额不足，请重新支付。\n");
    }
    else
    {
        printf("票价为: %d元\n", fare);
        printf("找零: %.2f元\n", change);
        // 计算每种面额的钞票张数
        for (int i = 0; i < 6; i++)
        {
            while (change >= bills[i])
            {
                change -= bills[i];
                count[i]++;
            }
        }
        // 输出找零面额张数
        printf("找零面额张数如下:\n");
        for (int i = 0; i < 6; i++)
        {
            if (count[i] > 0)
            {
                printf("%d元钞票: %d张\n", bills[i], count[i]);
            }
        }
    }
    return 0;
}

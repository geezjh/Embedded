#include <stdio.h>

int main()
{
    float BatteryMonitor, electricityFee;
    printf("请输入用电量: ");
    scanf("%f", &BatteryMonitor);
    if (BatteryMonitor <= 50)
    {
        electricityFee = BatteryMonitor * 0.538;
        printf("电费为: %.2f\n", electricityFee);
    }
    else if (BatteryMonitor <= 200)
    {
        electricityFee = (BatteryMonitor * 0.538) + (BatteryMonitor - 50) * 0.03;
        printf("电费为: %.2f\n", electricityFee);
    }
    else
    {
        electricityFee = (BatteryMonitor * 0.538) + (BatteryMonitor - 50) * 0.1;
        printf("电费为: %.2f\n", electricityFee);
    }
    return 0;
}
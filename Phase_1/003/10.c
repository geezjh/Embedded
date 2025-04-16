#include <stdio.h>
#include <math.h> // 使用ceil函数

int main()
{
    float money, charge, maxKm, extraKm;

    // 输入一个钱数
    printf("请输入一个钱数：");
    scanf("%f", &money);

    // 计算起步费用
    charge = 8.0;

    // 检查输入的钱数是否足够起步费用
    if (money < charge)
    {
        printf("输入的钱数不足起步费用8元。\n");
        return 0;
    }

    // 计算剩余的钱数
    money -= charge;

    // 计算超出起步公里数后的公里数
    extraKm = money / 1.8;

    // 总公里数为起步公里数加上超出的公里数，并向上取整
    maxKm = 3 + ceil(extraKm);

    // 输出最多能做的公里数
    printf("最多能做 %.2f 公里。\n", maxKm);

    return 0;
}

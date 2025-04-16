#include<stdio.h>

int main()
{
    float KmNum;
    printf("请输入公里数：");
    if(scanf("%f", &KmNum) != 1 || KmNum <= 0)
    {
        printf("请输入一个有效的正数。\n");
        return 1;
    }

    // 将公里数向上取整到最近的整数
    int roundedKmNum = (int)KmNum;
    if(KmNum - roundedKmNum > 0) {
        roundedKmNum++;
    }

    int b;
    if(roundedKmNum <= 3){
        b = 10;
        printf("您需要支付的费用是%d元\n", b);
    }else{
        b = 10 + (roundedKmNum - 3) * 2;
        printf("您需要支付的费用是%d元\n", b);
    }

    return 0;
}

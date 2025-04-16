#include <stdio.h>

int main()
{
    float a;
    printf("请输入水的体积：");
    if (scanf("%f", &a) != 1 || a <= 0)
    {
        printf("请输入一个有效的正数体积。\n");
        return 1; // 返回非零值表示程序异常退出
    }

    int b = 0;
    while (a > 0)
    {
        a -= 500;
        b++;
    }

    // 如果最后一次循环后水的体积不足500，b会多加了一次，需要减去1
    if (a < 0)
    {
        b--;
    }

    printf("能装%d瓶\n", b);
    return 0;
}

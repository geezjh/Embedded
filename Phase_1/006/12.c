#include <stdio.h>
void welcome()
{
    printf("*******************************************\n");
    printf("1、加法      2、减法    3、乘法\n");
    printf("4、除法      0、退出\n");
    printf("*******************************************\n");
}
void Calculate(int num, int a, int b)
{
    switch (num)
    {
    case 1:
        printf("%d+%d=%d\n", a, b, a + b);
        break;
    case 2:
        printf("%d-%d=%d\n", a, b, a - b);
        break;
    case 3:
        printf("%d*%d=%d\n", a, b, a * b);
        break;
    case 4:
        printf("%d/%d=%d\n", a, b, a / b);
        break;
    default:
        break;
    }
}
int main()
{
    welcome();
    int num, x1, x2;
    printf("请输入两个数：");
    scanf("%d%d", &x1, &x2);
    printf("请选择你要实现的功能：");
    scanf("%d", &num);
    Calculate(num, x1, x2);
    return 0;
}
#include <stdio.h>

int main()
{
    int year, moon;

    // 输入一个年份和月份
    printf("请输入一个年份和月份：");
    scanf("%d %d", &year, &moon);

    // 判断是否是闰年
    int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    // 根据月份和闰年情况输出天数
    switch (moon) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            printf("你输入的月份是%d,这个月一共有31天\n", moon);
            break;
        case 4: case 6: case 9: case 11:
            printf("你输入的月份是%d,这个月一共有30天\n", moon);
            break;
        case 2:
            if (isLeapYear) {
                printf("你输入的月份是%d,这个月一共有29天\n", moon);
            } else {
                printf("你输入的月份是%d,这个月一共有28天\n", moon);
            }
            break;
        default:
            printf("你输入的月份无效，请输入1到12之间的整数。\n");
            break;
    }

    return 0;
}

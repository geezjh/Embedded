#include <stdio.h>

int main()
{
    char b;
    int a, c;
    float result;

    // 输入一个算式：(例如：1+2)
    printf("请输入一个算式：(例如：1+2)\n");
    scanf("%d%c%d", &a, &b, &c);

    // 根据运算符进行计算
    switch (b) {
        case '+':
            result = (float)a + c;
            printf("该算式的结果为：%.2f\n", result);
            break;
        case '-':
            result = (float)a - c;
            printf("该算式的结果为：%.2f\n", result);
            break;
        case '*':
            result = (float)a * c;
            printf("该算式的结果为：%.2f\n", result);
            break;
        case '/':
            if (c == 0) {
                printf("除数不能为零。\n");
            } else {
                result = (float)a / c;
                printf("该算式的结果为：%.2f\n", result);
            }
            break;
        default:
            printf("无效的运算符，请输入 +, -, *, 或 /。\n");
            break;
    }

    return 0;
}
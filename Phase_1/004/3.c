/***********************************************************
  > File Name: 3.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月17日 星期五 20时06分38秒
    > Modified Time:2025年01月17日 星期五 20时14分07秒
 *******************************************************/

#include <stdio.h>

int main()
{
    int n;
    double sum = 1.00; // 初始化sum为1.00，因为第一项是1
    printf("please input a number:");
    scanf("%d", &n);

    if (n < 1) {
        printf("The number should be at least 1.\n");
        return 1;
    }

    for (int i = 2; i <= n; i++) {
        double term = 1.0 / i; // 使用浮点数除法
        if (i % 2 == 0) {
            sum += term;
        } else {
            sum -= term;
        }
    }

    printf("1 + ... + 1/%d 的结果是 %.2f\n", n, sum);
    return 0;
}



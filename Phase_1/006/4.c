#include <stdio.h>

// 自定义函数，计算各位数字的平方和
int sum_num(int num) {
    int sum = 0;
    int digit;

    // 处理负数的情况
    if (num < 0) {
        num = -num;
    }

    // 计算各位数字的平方和
    while (num > 0) {
        digit = num % 10; // 获取当前位的数字
        sum += digit * digit; // 将该数字的平方加到 sum 中
        num = num / 10; // 移除当前位的数字
    }

    return sum;
}

int main() {
    int num;
    printf("please input a number: ");
    scanf("%d", &num);
    int sum = sum_num(num);
    printf("sum of squares of digits = %d\n", sum);
    return 0;
}

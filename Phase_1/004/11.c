/***********************************************************
  > File Name: 11.c
  > Author: rose
  > Mail: 483086134@qq.com
  > Created Time: 2025年01月18日 星期六 16时18分50秒
    > Modified Time:2025年01月18日 星期六 16时23分04秒
 *******************************************************/

#include <stdio.h>

int main() {
    unsigned int num;
    unsigned int max = 0;  // 初始化最大值为0

    printf("请输入多个无符号整型数据，以0结束输入:\n");

    while (1) {
        scanf("%u", &num);  // 读取无符号整型数
        if (num == 0) {
            break;  // 如果输入为0，结束循环
        }
        if (num > max) {
            max = num;  // 更新最大值
        }
    }

    printf("输入数据中的最大值是: %u\n", max);

    return 0;
}


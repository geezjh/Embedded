// 确认电脑的主机字节序。大端（高字节的数据存放在低地址上，低字节的数据存放在高地址上），
// 小端（高字节的数据存放在高地址上，低字节的数据存放在低地址上））
#include <stdio.h>

// 判断字节序的函数
int check_endianness()
{
    // 定义一个整型变量，值为 1
    int num = 1;
    // 将整型变量的地址强制转换为字符指针
    char *ptr = (char *)&num;
    // 如果最低地址处的字节值为 1，说明是小端字节序
    if (*ptr == 1)
    {
        return 0; // 小端字节序
    }
    else
    {
        return 1; // 大端字节序
    }
}

int main()
{
    int result = check_endianness();
    if (result == 0)
    {
        printf("这台计算机使用的是小端字节序。\n");
    }
    else
    {
        printf("这台计算机使用的是大端字节序。\n");
    }
    return 0;
}
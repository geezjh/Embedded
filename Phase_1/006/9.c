#include <stdio.h>

void Count(char a[], int n)
{
    int count = 0;        // 初始化计数器
    int hasUppercase = 0; // 标志是否有大写字母

    for (int i = 0; i < n; i++)
    {
        if (a[i] >= 65 && a[i] <= 90)
        {
            count++;
            hasUppercase = 1; // 发现大写字母，设置标志
        }
    }

    if (hasUppercase)
    {
        printf("大写字母个数为：%d\n", count);
    }
    else
    {
        printf("该字符串无大写字母\n");
    }
}

int main()
{
    char a[6];                  // 确保数组有足够的空间存储5个字符和一个结束符
    printf("请输入5个字符:\n"); // 添加换行符以便提示信息清晰
    fgets(a, 6, stdin);         // 读取5个字符，包括结束符
    Count(a, 5);
    return 0;
}

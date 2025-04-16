#include <stdio.h>

// 计算字符串长度
void my_length(char *p)
{
    int n = 0;
    while (*p != '\0')
    {
        n++;
        p++;
    }
    printf("该字符串的长度为：%d\n", n);
}

// 统计字符串中大写字母的个数
void count_letter(char *p)
{
    int n = 0;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            n++;
        }
        p++;
    }
    printf("在该字符串中大写字母的个数为：%d\n", n);
}

// 统计字符串中数字字符的个数
void count_num(char *p)
{
    int n = 0;
    while (*p != '\0')
    {
        if (*p >= '0' && *p <= '9')
        {
            n++;
        }
        p++;
    }
    printf("在该字符串中数字字符的个数为：%d\n", n);
}

int main()
{
    char str[100];
    printf("请输入一个字符串：");
    scanf("%s", str);
    my_length(str);
    count_letter(str);
    count_num(str);
    return 0;
}

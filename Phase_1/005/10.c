#include <stdio.h>
#include <string.h>

void my_strcat(char dest[], const char src[])
{
    int i = 0;
    int j = 0;

    // 找到 dest 字符串的结尾
    while (dest[i] != '\0')
    {
        i++;
    }

    // 将 src 字符串的内容追加到 dest 字符串的末尾
    while (src[j] != '\0')
    {
        dest[i + j] = src[j];
        j++;
    }

    // 添加字符串结束符
    dest[i + j] = '\0';
}

int main()
{
    char str1[20] = "hello";
    char str2[6] = "world";

    // 计算 str1 的长度
    int len1 = 0;
    while (str1[len1] != '\0')
    {
        len1++;
    }

    // 计算 str2 的长度
    int len2 = 0;
    while (str2[len2] != '\0')
    {
        len2++;
    }

    // 调用自定义的 strcat 函数
    my_strcat(str1, str2);

    // 打印追加后的字符串
    printf("After concatenation: %s\n", str1);

    return 0;
}

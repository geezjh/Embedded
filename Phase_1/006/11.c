#include <stdio.h>

void is_num(char a)
{
    if (a >= '0' && a <= '9')
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
}
int main()
{
    char a;
    printf("请输入一个字符：\n");
    scanf("%c", &a);
    is_num(a);
    return 0;
}
